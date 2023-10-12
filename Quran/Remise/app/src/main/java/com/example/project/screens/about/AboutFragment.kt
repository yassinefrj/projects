package com.example.project.screens.about

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import com.example.project.R
import com.example.project.database.ChapterListDatabase
import com.example.project.databinding.FragmentAboutBinding


class AboutFragment : Fragment() {

    private lateinit var binding : FragmentAboutBinding

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        binding = DataBindingUtil.inflate(inflater,
            R.layout.fragment_about,container,false)

        binding.buttonClearDB.setOnClickListener { clearDB() }

        return binding.root
    }

    private fun clearDB() {
        val database = ChapterListDatabase.getInstance(this.requireContext())
        database.dao().clearTable()
    }


}