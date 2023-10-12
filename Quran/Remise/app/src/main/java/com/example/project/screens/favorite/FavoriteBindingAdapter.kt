package com.example.project.screens.favorite

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.project.database.ChapterJSON
import com.example.project.databinding.FavoriteItemLayoutBinding

class FavoriteAdapter(private val clickListener : FavoriteListener) : ListAdapter<ChapterJSON,FavoriteAdapter.ViewHolder>(FavoriteDiffUtil()){

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        return ViewHolder.from(parent)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val itemToShow = getItem(position)
        holder.bind(itemToShow,clickListener)
    }



    class ViewHolder private constructor(val binding : FavoriteItemLayoutBinding) : RecyclerView.ViewHolder(binding.root){

        fun bind(
            itemToShow: ChapterJSON,
            clickListener: FavoriteListener
        ) {
            binding.chapterItem = itemToShow
            binding.favoriteListener = clickListener
        }

        companion object{
            fun from(parent: ViewGroup): ViewHolder {
                val layoutInflater = LayoutInflater.from(parent.context)
                val binding = FavoriteItemLayoutBinding.inflate(layoutInflater,parent,false)
                return ViewHolder(binding)
            }
        }
    }

}

class FavoriteDiffUtil : DiffUtil.ItemCallback<ChapterJSON>(){
    override fun areItemsTheSame(oldItem: ChapterJSON, newItem: ChapterJSON): Boolean {
        return oldItem.id == newItem.id
    }

    override fun areContentsTheSame(oldItem: ChapterJSON, newItem: ChapterJSON): Boolean {
        return oldItem == newItem
    }

}

class FavoriteListener(val clickListener : (idChapterJSON: Int) -> Unit){
    fun onClick(chapter : ChapterJSON) = clickListener(chapter.id)
}