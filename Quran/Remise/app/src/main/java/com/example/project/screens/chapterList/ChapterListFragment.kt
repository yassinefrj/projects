package com.example.project.screens.chapterList

import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.fragment.findNavController
import com.example.project.R
import com.example.project.databinding.FragmentChapterListBinding


class ChapterListFragment : Fragment() {
    private lateinit var binding: FragmentChapterListBinding
    private lateinit var vm : ChapterListViewModel
    private lateinit var vmFactory : ChapterListViewModelFactory

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        val application = requireActivity().application

        // init VM using VMFactory
        vmFactory = ChapterListViewModelFactory(application)
        vm = ViewModelProvider(this,vmFactory).get(ChapterListViewModel::class.java)

        // init of binding object
        binding = DataBindingUtil.inflate(inflater,R.layout.fragment_chapter_list,container,false)

        // init of Adapter (RecyclerView)
        val adapter = ChapterAdapter(ChapterListener { idChapter ->
            Log.i("DEBUG", "ChapterListFragment - adapter - ChapterListener - init")
            // handle the click on a chapter name
            vm.onChapterNameClicked(idChapter)
            vm.incrementChapterCount(idChapter)
        }, DownloadListener { idChapter ->
            Log.i("DEBUG", "ChapterListFragment - adapter - DownloadListener - init")
            vm.onChapterDownloadClicked(idChapter)
        })

        // set the adapter to the binding object
        binding.recyclerView.adapter = adapter

        // Make the navigation
        vm.navigateToChapter.observe(viewLifecycleOwner, Observer { chapterId ->
            Log.i("DEBUG", "ChapterListFragment - vm.navigateToChapter.observe - CHECK")
            if(chapterId != -1){
                this.findNavController().navigate(ChapterListFragmentDirections.actionChapterListFragmentToChapterFragment(chapterId))
                vm.onChapterFragmentNavigated()
            }
        })

        // Show a message if the connexion is not ON
        vm.connexionOn.observe(viewLifecycleOwner, Observer { connexionOn ->
            Log.i("DEBUG", "ChapterListFragment - vm.connexionOn.observe - CHECK")
            if (connexionOn != null){
                if(connexionOn == false){
                    Toast.makeText(context, R.string.noConnexion,Toast.LENGTH_LONG).show()
                    vm.afterConnexionFalse()
                }
            }
        })

        // DATA BASE PART
        vm.chaptersDB.observe(viewLifecycleOwner, Observer { chaptersDB ->
            Log.i("DEBUG", "ChapterListFragment - vm.chaptersDB.observe - CHECK")
            if (chaptersDB != null){
                Log.i("DB", "get data from db in fragment")
                    if(chaptersDB.isNotEmpty()){
                        Log.i("DEBUG", "ChapterListFragment - vm.chaptersDB.observe - show data from DB")
                        adapter.submitList(chaptersDB.toMutableList())
                    }else{
                        Log.i("DEBUG", "ChapterListFragment - vm.chaptersDB.observe - get data from API request")
                        vm.sendApiRequest()
                    }

            }
        })

        return binding.root
    }
}