package com.example.project.screens.infos

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import com.example.project.R
import com.example.project.databinding.FragmentInfosChapterBinding
import com.example.project.screens.reading.ChapterFragmentArgs

class InfosChapterFragment : Fragment() {
    private lateinit var binding : FragmentInfosChapterBinding
    private lateinit var vm : InfosChapterViewModel
    private lateinit var vmFactory : InfosChapterViewModelFactory

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // getIdChapter
        val arguments = ChapterFragmentArgs.fromBundle(requireArguments())

        // init ViewModel using ViewModelProvider
        val application = requireActivity().application
        vmFactory = InfosChapterViewModelFactory(arguments.chapterId,application)
        vm = ViewModelProvider(this,vmFactory).get(InfosChapterViewModel::class.java)

        // init Binding object of the xml view
        binding = DataBindingUtil.inflate(inflater,R.layout.fragment_infos_chapter,container,false)

        vm.connexionOn.observe(viewLifecycleOwner, Observer { connexion ->
            if (connexion != null){
                if (connexion == false){
                    Toast.makeText(context,R.string.noConnexion,Toast.LENGTH_LONG).show()
                }
            }
        })

        vm.nameSimple.observe(viewLifecycleOwner, Observer { nameSurat ->
            if (nameSurat != null){
                binding.titleSurat.text = nameSurat
            }
        })
        vm.text.observe(viewLifecycleOwner, Observer { contentText ->
            if (contentText != null){
                binding.contentInfosSurat.text = contentText
            }
        })

        vm.source.observe(viewLifecycleOwner, Observer { sourceText ->
            if (sourceText != null){
                binding.contentInfosSuratSource.text = sourceText
            }
        })

        return binding.root
    }
}