package com.example.project.screens.reading

import android.app.Application
import android.util.Log
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.project.database.*
import com.example.project.network.Network
import com.example.project.repository.Repository
import com.google.gson.Gson
import java.io.File

class ChapterViewModel(private val chapterId: Int, val app : Application) : AndroidViewModel(app) {

    val repository = Repository(app.applicationContext)
    private val network = Network()

    private var _listVerse = MutableLiveData<List<Verse>>()
    val listVerse: LiveData<List<Verse>>
        get() = _listVerse

    private var nbOfVerse: Int = 0
    private var compteur: Int = 0

    private var _connexionOn = MutableLiveData<Boolean>()
    val connexionOn : LiveData<Boolean>
        get() = _connexionOn

    private var _nameSimple = MutableLiveData<String>()
    val nameSimple : LiveData<String>
     get() = _nameSimple

    init {
        _connexionOn.value = true
        _nameSimple.value = repository.dao.getNameById(chapterId)

        val chapterContent : ChapterJSON? = repository.dao.get(chapterId)
        if(chapterContent != null && chapterContent.isDownloaded){
            // la data se trouve en local
            Log.i("LOCAL", "ChapterViewModel - DATA EN LOCAL ")

            val filePath = chapterContent.pathInLocal

            val verseJSONList : VerseJSONList? = loadVerseJSONListFromFile(filePath)
            _listVerse.value = verseJSONList?.verses
            Log.i("LOCAL", "ChapterViewModel - DATA GET ")
        }else{
            getSomeVerses(1)
        }
    }

    private fun loadVerseJSONListFromFile(filePath: String?): VerseJSONList? {
        val file = File(filePath)
        if (file.exists()) {
            val jsonString = file.readText()
            return Gson().fromJson(jsonString, VerseJSONList::class.java)
        }
        return null
    }

    private fun getNumberOfVerses() {

        network.sendRequestChapterById(chapterId, object : Network.RequestChapterCallback {
            override fun onChapterReceived(chapter: ChapterResponse) {
                Log.i("HTTPS", "sendRequestChapterById - SHOW DATA")
                nbOfVerse = chapter.chapter.verses_count

                if (nbOfVerse != null) {

                    if (nbOfVerse.div(50) >= 1) {
                        compteur++
                        if (compteur * 50 <= nbOfVerse) {
                            getSomeVerses(compteur + 1)
                        }
                    }
                }
            }

            override fun onError() {
                Log.i("HTTPS", "sendRequestChapterById - FAILLURE ")
                _connexionOn.value = false
            }
        })
    }

    private fun getSomeVerses(pageNumber: Int) {
        network.sendRequestVerseByChapterId(
            chapterId,
            pageNumber,
            object : Network.RequestVersesCallback {
                override fun onVerseReceived(verseJSON: VerseJSONList) {
                    Log.i("HTTPS", "sendRequestVerseByChapterId - SHOW DATA")

                    if (_listVerse.value == null) {
                        Log.i("HTTPS", "Premiere init")
                        _listVerse.value = verseJSON.verses
                        getNumberOfVerses()
                    } else {
                        Log.i("HTTPS", "Next init")

                        if (_listVerse != null) {
                            val currentList = _listVerse.value ?: emptyList()
                            val newList = currentList + verseJSON.verses
                            _listVerse.value = newList
                            compteur++
                            if (compteur * 50 <= nbOfVerse) {
                                getSomeVerses(compteur + 1)
                            }else{
                                Log.i("HTTPS","LA C FINI")
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

    fun afterConnexionFalse(){
        _connexionOn.value = true
    }

}