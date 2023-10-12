package com.example.project.screens.favorite

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.project.database.ChapterJSON
import com.example.project.database.ChapterListDatabase
import com.example.project.network.Network
import com.example.project.repository.Repository

class FavoriteViewModel(application: Application) : AndroidViewModel(application) {

    val repository = Repository(application.applicationContext
    )
    val chaptersDB: LiveData<List<ChapterJSON>> = repository.dao.getAllFavoriteChapters()

    private var _navigateToChapter = MutableLiveData<Int>()
    val navigateToChapter : LiveData<Int>
        get() = _navigateToChapter

    fun onChapterNameClicked(idChapter: Int) {
        _navigateToChapter.value = idChapter
    }

    fun incrementChapterCount(idChapter: Int) {
        repository.dao.incrementChapterCount(idChapter)
    }

    fun onChapterFragmentNavigated() {
        _navigateToChapter.value = -1 // try null
    }
}