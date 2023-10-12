package com.example.project.screens.reading

import android.app.Application
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider

class ChapterViewModelFactory(private val chapterId : Int, private val app : Application) : ViewModelProvider.Factory{
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(ChapterViewModel::class.java)) {
            return ChapterViewModel(chapterId,app) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}