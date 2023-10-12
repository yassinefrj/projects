package com.example.project.screens.chapterList

import androidx.databinding.BindingAdapter
import com.example.project.R
import com.example.project.database.ChapterJSON
import com.google.android.material.button.MaterialButton

@BindingAdapter("suratName")
fun MaterialButton.setSuratName(item : ChapterJSON?){
    if(item != null){
        val suratName = context.getString(R.string.surat_name_format, item.id, item.name_simple)
        text = suratName
    }
}

@BindingAdapter("setIsEnabled")
fun MaterialButton.setIsEnabled(item : ChapterJSON?){
    if (item != null){
        if (item.isDownloaded){
            isClickable = false
            isEnabled = false
            text = context.getString(R.string.downloaded)
        }else{
            isClickable = true
            isEnabled = true
            text = context.getString(R.string.download)
        }

    }
}