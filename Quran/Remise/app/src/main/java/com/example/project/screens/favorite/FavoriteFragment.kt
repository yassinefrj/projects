package com.example.project.screens.favorite

import android.os.Bundle
import android.view.*
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import androidx.navigation.fragment.findNavController
import androidx.navigation.ui.NavigationUI
import androidx.recyclerview.widget.GridLayoutManager
import com.example.project.R
import com.example.project.databinding.FragmentFavoriteBinding


class FavoriteFragment : Fragment() {

    private lateinit var binding: FragmentFavoriteBinding
    private lateinit var vm: FavoriteViewModel
    private lateinit var vmFactory : FavoriteViewModelFactory


    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_favorite, container, false
        )

        setHasOptionsMenu(true) // indique que ce Fragment a un menu a afficher

        val application = requireActivity().application
        vmFactory = FavoriteViewModelFactory(application)
        vm = ViewModelProvider(this,vmFactory).get(FavoriteViewModel::class.java)

        // init of adapter and handle click
        val adapter = FavoriteAdapter(FavoriteListener { idChapterJSON: Int ->
            if (idChapterJSON != null){
                vm.onChapterNameClicked(idChapterJSON)
                vm.incrementChapterCount(idChapterJSON)
            }
        })

        binding.favoriteRecyclerView.adapter = adapter

        //shows data in recycler view
        vm.chaptersDB.observe(viewLifecycleOwner, Observer { chaptersDB->
            if (chaptersDB != null){
                val chaptersDBSorted = chaptersDB.sortedByDescending { it.count }
                adapter.submitList(chaptersDBSorted)
            }
        })

        // navigation to chapterFragment
        vm.navigateToChapter.observe(viewLifecycleOwner, Observer { chapterId ->
            if(chapterId != -1){
                this.findNavController().navigate(FavoriteFragmentDirections.actionFavoriteFragmentToChapterFragment(chapterId))
                vm.onChapterFragmentNavigated()
            }
        })

        val layoutManager = GridLayoutManager(this.activity,1,GridLayoutManager.HORIZONTAL,false)
        binding.favoriteRecyclerView.layoutManager = layoutManager

        return binding.root
    }

    /**
     * Affichage du du menu
     */
    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.options_menu, menu)
    }

    /**
     * Gestion du click sur un item du menu
     * v1 (About itm only)
     */
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return NavigationUI.onNavDestinationSelected(item, requireView().findNavController())
                || super.onOptionsItemSelected(item)
    }



}