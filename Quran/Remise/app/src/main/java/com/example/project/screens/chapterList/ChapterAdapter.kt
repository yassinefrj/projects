package com.example.project.screens.chapterList

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.RecyclerView
import com.example.project.database.ChapterJSON
import com.example.project.databinding.ChapterItemLayoutBinding

class ChapterAdapter(private val clickListener : ChapterListener,private val downloadListener: DownloadListener) : ListAdapter<ChapterJSON,ChapterAdapter.ViewHolder>(ChapterDiffCallBack()) {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        return ViewHolder.from(parent)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val itemToShow = getItem(position)
        holder.bind(itemToShow, clickListener,downloadListener)
    }

    class ViewHolder private constructor(val binding : ChapterItemLayoutBinding) : RecyclerView.ViewHolder(binding.root){

        fun bind(
            itemToShow: ChapterJSON,
            clickListener: ChapterListener,
            downloadListener: DownloadListener
        ) {
            binding.chapterJSON = itemToShow
            binding.listenerChapterToRead = clickListener
            binding.listenerChapterToDownload = downloadListener
        }

        companion object{
             fun from(parent: ViewGroup): ViewHolder {
                 val layoutInflater = LayoutInflater.from(parent.context)
                 val binding = ChapterItemLayoutBinding.inflate(layoutInflater,parent,false)
                 return ViewHolder(binding)
            }
        }
    }
}

/**
 * Class used to update efficiently the content of the recycler view
 */
class ChapterDiffCallBack : DiffUtil.ItemCallback<ChapterJSON>() {
    override fun areItemsTheSame(oldItem: ChapterJSON, newItem: ChapterJSON): Boolean {
        return oldItem.id == newItem.id
    }

    override fun areContentsTheSame(oldItem: ChapterJSON, newItem: ChapterJSON): Boolean {
        return oldItem == newItem
    }
}

class ChapterListener (val clickListener : (chapterId : Int) -> Unit){
    fun onClick(chapter : ChapterJSON) = clickListener(chapter.id)
}

class DownloadListener (val clicklistener : (chapterId : Int) -> Unit){
    fun onClick(chapter : ChapterJSON) = clicklistener(chapter.id)
}

