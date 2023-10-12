package com.example.project.screens.infos

import android.app.Application
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider

class InfosChapterViewModelFactory(private var chapterId : Int,val app : Application) : ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(InfosChapterViewModel::class.java)) {
            return InfosChapterViewModel(chapterId,app) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}