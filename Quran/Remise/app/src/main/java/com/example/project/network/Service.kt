package com.example.project.network

import com.example.project.database.ChapterInfoResponse
import com.example.project.database.ChapterJSONList
import com.example.project.database.ChapterResponse
import com.example.project.database.VerseJSONList
import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Path
import retrofit2.http.Query

interface Service {
    @GET("v4/chapters?language=en")
    fun getChapters() : Call<ChapterJSONList>

    @GET("v4/verses/by_chapter/{idChapter}")
    fun getVersesByChapterId(
        @Path("idChapter") idChapter: Int,
        @Query("page") pageNumber: Int,
        @Query("language") language: String = "en",
        @Query("words") words: Boolean = true,
        @Query("per_page") perPage: Int = 50
    ): Call<VerseJSONList>


    @GET("v4/chapters/{idChapter}?language=en")
    fun getChapterById(@Path("idChapter") idChapter: Int): Call<ChapterResponse>



    @GET("v4/chapters/{chapter_id}/info")
    fun getChapterInfoById(@Path("chapter_id") chapter_id: Int,
                           @Query("language") language: String = "en",): Call<ChapterInfoResponse>





}