package com.example.project.screens.reading

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.RecyclerView
import com.example.project.database.Verse
import com.example.project.databinding.VerseItemLayoutBinding


class VerseAdapter : ListAdapter<Verse,VerseAdapter.ViewHolder>(VerseDiffCallBack()) {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        return ViewHolder.from(parent)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val itemToShow = getItem(position)
        holder.bind(itemToShow)

    }



    class ViewHolder private constructor(val binding : VerseItemLayoutBinding) : RecyclerView.ViewHolder(binding.root){
        fun bind(
            itemToShow: Verse,
        ) {
            binding.verse = itemToShow
        }

        companion object{
            fun from(parent: ViewGroup): ViewHolder {
                val layoutInflater = LayoutInflater.from(parent.context)
                val binding =  VerseItemLayoutBinding.inflate(layoutInflater,parent,false)
                return ViewHolder(binding)
            }
        }
    }
}

class VerseDiffCallBack : DiffUtil.ItemCallback<Verse>(){
    override fun areItemsTheSame(oldItem: Verse, newItem: Verse): Boolean {
        return oldItem.id == newItem.id
    }

    override fun areContentsTheSame(oldItem: Verse, newItem: Verse): Boolean {
        return oldItem == newItem
    }

}



//class VerseItemViewHolder(val textView : TextView) : RecyclerView.ViewHolder(textView)