package com.example.project.database

import androidx.lifecycle.LiveData
import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import com.example.project.database.ChapterJSON

@Dao
interface ChapterListDao {

    @Insert
    fun add(chapter : ChapterJSON)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insertAll(chapters: List<ChapterJSON>)

    @Query("SELECT * FROM chapter_list WHERE id = :idChapter ")
    fun get(idChapter : Int) : ChapterJSON?

    @Query("SELECT * FROM chapter_list")
    fun getAllChapters(): LiveData<List<ChapterJSON>>

    @Query("SELECT * FROM chapter_list WHERE count > 0")
    fun getAllFavoriteChapters(): LiveData<List<ChapterJSON>>

    @Query("SELECT COUNT(*) FROM chapter_list")
    fun getChaptersCount(): Int

    @Query("UPDATE chapter_list SET count = count + 1 WHERE id = :chapterId")
    fun incrementChapterCount(chapterId: Int)

    @Query("UPDATE chapter_list SET isDownloaded = 1, pathInLocal = :newPath WHERE id = :chapterId")
    fun updateChapterInfo(chapterId: Int, newPath: String)

    @Query("DELETE FROM chapter_list")
    fun clearTable()

    @Query("SELECT name_simple FROM chapter_list WHERE id = :chapterId")
    fun getNameById(chapterId: Int): String

}