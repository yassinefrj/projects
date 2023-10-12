package com.example.project.screens.infos

import android.app.Application
import android.text.Html
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.project.database.ChapterInfoResponse
import com.example.project.database.ChapterListDatabase

import com.example.project.network.Network
import com.example.project.repository.Repository

class InfosChapterViewModel(private val chapterId : Int,val app : Application) : AndroidViewModel(app) {

    private var _text = MutableLiveData<CharSequence>()
    val text : LiveData<CharSequence>
        get() = _text

    private var _source = MutableLiveData<CharSequence>()
    val source : LiveData<CharSequence>
        get() = _source

    private var _connexionOn = MutableLiveData<Boolean>()
    val connexionOn : LiveData<Boolean>
        get() = _connexionOn

    private var _nameSimple = MutableLiveData<String>()
    val nameSimple : LiveData<String>
        get() = _nameSimple

    val repository = Repository(app.applicationContext)

    init {
        _nameSimple.value = repository.dao.getNameById(chapterId)

        val network = Network()
        network.sendRequestChapterInfosById(chapterId, object : Network.RequestChapterInfosCallback {
            override fun onChapterInfosReceived(chapter: ChapterInfoResponse) {

                if (chapter != null){
                    val htmlText = chapter.chapter_info.text
                    val styledText = Html.fromHtml(htmlText)

                    _text.value = styledText

                    val sourceJson: String? = chapter.chapter_info.source
                    sourceJson.let {
                        _source.value = it
                    }
                }
            }

            override fun onError() {
                _connexionOn.value = false
            }
        })
    }
}