package com.example.project.database

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [ChapterJSON::class], version = 3, exportSchema = false)
abstract class ChapterListDatabase : RoomDatabase() {

    abstract fun dao() : ChapterListDao

    companion object {
        @Volatile
        private var INSTANCE: ChapterListDatabase? = null

        fun getInstance(context: Context): ChapterListDatabase {
            synchronized(this){
                var instance = INSTANCE
                if (instance == null) {
                    instance = Room.databaseBuilder(
                        context.applicationContext,
                        ChapterListDatabase::class.java,
                        "chapter_list_database"
                    ).fallbackToDestructiveMigration().allowMainThreadQueries().build()
                    INSTANCE = instance
                }
                return instance
            }
        }
    }
}
