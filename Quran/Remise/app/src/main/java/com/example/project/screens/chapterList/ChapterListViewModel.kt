package com.example.project.screens.chapterList

import android.app.Application
import android.util.Log
import android.widget.Toast
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.project.R
import com.example.project.database.*
import com.example.project.network.Network
import com.example.project.repository.Repository
import java.io.File
import com.google.gson.Gson


class ChapterListViewModel(val app: Application) : AndroidViewModel(app) {

    val repository = Repository(app.applicationContext)

    private val network = Network()

    /**
     * Contains the chapter list saved in DB
     */
    val chaptersDB = repository.dao.getAllChapters()


    private var _connexionOn = MutableLiveData<Boolean>()
    val connexionOn : LiveData<Boolean>
        get() = _connexionOn

    private var _navigateToChapter = MutableLiveData<Int>()
    val navigateToChapter : LiveData<Int>
        get() = _navigateToChapter

    /**
     * Used for verses in local save
     */
    private var nbOfVerse: Int = 0
    private var compteur: Int = 0
    private var _listVerse = MutableLiveData<List<Verse>>()
    private var connexionOnDownloadOn : Boolean = true

    init {
        Log.i("DEBUG", "ChapterListViewModel - init")
        _navigateToChapter.value = -1
        _connexionOn.value = true
    }

    fun sendApiRequest() {
        if (repository.dao.getChaptersCount() == 0) {
            network.sendRequest(object : Network.RequestCallback {
                override fun onChaptersReceived(chaptersList: ChapterJSONList) {
                    Log.i("HTTPS", "Pas de data donc api request")
                    // Stockez la liste de chapitres dans une db
                    val dataToSaveInDB = mutableListOf<ChapterJSON>()
                    for (chapter in chaptersList.chapters) {
                        dataToSaveInDB.add(chapter)
                    }
                    repository.dao.insertAll(dataToSaveInDB)
                    Log.i("DB", "saved")
                }
                override fun onError() {
                    Log.i("HTTPS", "ON ERROR")
                    _connexionOn.value = false
                }
            })
        } else {
            // get data from db
            Log.i("DB", "get data from db in vm")
        }
    }

    fun onChapterNameClicked(idChapter : Int){
        _navigateToChapter.value = idChapter
    }

    fun onChapterFragmentNavigated(){
        _navigateToChapter.value = -1 // try null
    }

    fun afterConnexionFalse(){
        _connexionOn.value = true
    }

    fun incrementChapterCount(idChapter: Int) {
        repository.dao.incrementChapterCount(idChapter)
    }

    // STORAGE IN LOCAL PART

    fun onChapterDownloadClicked(idChapter: Int) {
        // remettre nbOfVerse et compteur a 0 (zero) for later use by precaution
        nbOfVerse = 0
        compteur = 0
        // vider _listVerse
        _listVerse.value = emptyList()
        // remise de connexionOnDownloadOn a sa valeur par defaut
        connexionOnDownloadOn = true

        // launch an API request and save the MutableList<Verse> in _listVerse property
        getSomeVerses(1,idChapter)
    }

    fun tryToSaveInLocal(idChapter : Int){
        if (!connexionOnDownloadOn){
            Toast.makeText(app.applicationContext, R.string.noConnexion,Toast.LENGTH_LONG).show()
            return
        }

        // update db
        val chapterContent: ChapterJSON? = repository.dao.get(idChapter)
        chapterContent?.pathInLocal = idChapter.toString()
        val filePath = app.applicationContext.filesDir.absolutePath + File.separator + chapterContent?.pathInLocal
        repository.dao.updateChapterInfo(idChapter,filePath)

        // save in local
        val list = _listVerse.value?.toList()
        if (list != null){
            saveVerseJSONListToFile(VerseJSONList(list),filePath)
        }
    }

    // Sérialisation des données
    private fun saveVerseJSONListToFile(verseJSONList: VerseJSONList, filePath: String) {
        val gson = Gson()
        val jsonString = gson.toJson(verseJSONList)
        val file = File(filePath)
        file.writeText(jsonString)
        Log.i("LOCAL", "saveVerseJSONListToFile - data saved")
    }

    private fun getNumberOfVerses(chapterId : Int) {

        network.sendRequestChapterById(chapterId, object : Network.RequestChapterCallback {
            override fun onChapterReceived(chapter: ChapterResponse) {
                Log.i("HTTPS", "sendRequestChapterById - SHOW DATA")
                nbOfVerse = chapter.chapter.verses_count

                if (nbOfVerse != null) {

                    if (nbOfVerse.div(50) >= 1) {
                        compteur++
                        if (compteur * 50 <= nbOfVerse) {
                            getSomeVerses(compteur + 1,chapterId)
                        }else{
//                            Log.i("HTTPS","FINISH NORMAL") never called
                        }
//                        do {
//
//                            compteur++
//                        } while (compteur * 50 <= nbOfVerse)
                    }else{
                        Log.i("HTTPS","FINISH SHORT")
                        tryToSaveInLocal(chapterId)
                    }
                }

            }

            override fun onError() {
                Log.i("HTTPS", "sendRequestChapterById - FAILLURE ")
                _connexionOn.value = false
            }
        })
    }

    private fun getSomeVerses(pageNumber: Int, chapterId: Int) {
        network.sendRequestVerseByChapterId(
            chapterId,
            pageNumber,
            object : Network.RequestVersesCallback {
                override fun onVerseReceived(verseJSON: VerseJSONList) {
                    Log.i("HTTPS", "sendRequestVerseByChapterId - SHOW DATA")

                    if (_listVerse.value?.isEmpty() == true) {
                        Log.i("HTTPS", "Premiere init - first part of data get")
                        _listVerse.value = verseJSON.verses
                        getNumberOfVerses(chapterId)
                    } else {
                        Log.i("HTTPS", "Next init")

                        if (_listVerse != null) {
                            val currentList = _listVerse.value ?: emptyList()
                            val newList = currentList + verseJSON.verses
                            _listVerse.value = newList
                            compteur++
                            if (compteur * 50 <= nbOfVerse) {
                                getSomeVerses(compteur + 1,chapterId)
                            }else{
                                Log.i("HTTPS","FINISH LONG")
                                tryToSaveInLocal(chapterId)
                            }
                        }

                    }
                }

                override fun onError() {
                    Log.i("HTTPS", "sendRequestVerseByChapterId - FAILLURE ")
                    _connexionOn.value = false
                }

            })
    }



}