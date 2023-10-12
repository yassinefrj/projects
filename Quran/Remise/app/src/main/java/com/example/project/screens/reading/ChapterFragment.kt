package com.example.project.screens.reading

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.fragment.findNavController
import com.example.project.R
import com.example.project.databinding.FragmentChapterBinding


class ChapterFragment : Fragment() {
    private lateinit var vm : ChapterViewModel
    private lateinit var vmFactory : ChapterViewModelFactory
    private lateinit var binding : FragmentChapterBinding

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        // getIdChapter
        val arguments = ChapterFragmentArgs.fromBundle(requireArguments())

        // init ViewModel using ViewModelProvider
        val application = requireActivity().application
        vmFactory = ChapterViewModelFactory(arguments.chapterId,application)
        vm = ViewModelProvider(this,vmFactory).get(ChapterViewModel::class.java)

        // init Binding object of the xml view
        binding = DataBindingUtil.inflate(inflater,R.layout.fragment_chapter,container,false)

        // init adapter and connect it with the xml recycler view
        val adapter = VerseAdapter()
        binding.recyclerView.adapter = adapter

        // observe the JSON list of verses
        vm.listVerse.observe(viewLifecycleOwner, Observer { listVerse ->
            Log.i("HTTPS", "SHOW DATA")
            if (listVerse != null){ // principe de precaution
                adapter.submitList(listVerse)
            }
        })

        vm.connexionOn.observe(viewLifecycleOwner, Observer { connexionOn ->
            if (connexionOn != null){
                if (connexionOn == false){
                    Log.i("HTTPS", "sendRequestChapterById - NO CONNEXION ")
                    Toast.makeText(context,R.string.noConnexion,Toast.LENGTH_LONG).show()
                    vm.afterConnexionFalse()
                }
            }
        })

        vm.nameSimple.observe(viewLifecycleOwner, Observer { nameSurat ->
            if (nameSurat != null){
                binding.titleSurat.text = nameSurat
            }
        })

        binding.buttonInfos.setOnClickListener { onButtonInfosClicked(arguments.chapterId) }

        return binding.root
    }

    private fun onButtonInfosClicked(chapterId : Int){
        this.findNavController().navigate(ChapterFragmentDirections.actionChapterFragmentToInfosChapterFragment(chapterId))
    }

}