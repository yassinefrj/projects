package com.example.project.screens.chapterList

import android.app.Application
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider

class ChapterListViewModelFactory(private val application: Application) : ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(ChapterListViewModel::class.java)) {
            return ChapterListViewModel(application) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}