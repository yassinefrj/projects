package com.example.project.screens.favorite

import androidx.databinding.BindingAdapter
import com.example.project.R
import com.example.project.database.ChapterJSON
import com.google.android.material.button.MaterialButton

@BindingAdapter("setSuratName")
fun MaterialButton.setSuratName(item : ChapterJSON?){
    if (item != null){
        val suratName = context.getString(R.string.surat_name_format, item.id, item.name_simple)
        text = suratName
    }
}