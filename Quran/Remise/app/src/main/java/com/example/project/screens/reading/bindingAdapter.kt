package com.example.project.screens.reading

import android.widget.TextView
import androidx.databinding.BindingAdapter
import com.example.project.database.Verse

@BindingAdapter("verseContent")
fun TextView.setVerseContent(item : Verse?){
    if (item != null){
        val oneVerse = StringBuilder()
        for (word in item.words) {
            val translation = word.translation
            if (translation != null) {
                val text = translation.text
                if (text != null) {
                    oneVerse.append(text)
                    oneVerse.append(" ")
                }
            }
        }
        text = oneVerse
    }
}