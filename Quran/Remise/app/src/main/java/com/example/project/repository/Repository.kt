package com.example.project.repository

import android.content.Context
import com.example.project.database.ChapterListDatabase

class Repository(context: Context) {

    val database = ChapterListDatabase.getInstance(context)
    val dao = database.dao()


}