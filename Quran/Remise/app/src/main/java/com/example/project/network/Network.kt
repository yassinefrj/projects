package com.example.project.network


import android.util.Log
import com.example.project.database.*
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.moshi.MoshiConverterFactory

class Network {
    private lateinit var myHttpClient : Service

    init {
        val baseUrl = "https://api.quran.com/api/"
        // create a converter JSON -> Kotlin
        val jsonConverter: MoshiConverterFactory = MoshiConverterFactory.create()
        // create a Retrofit builder
        val retrofitBuiler: Retrofit.Builder =
            Retrofit.Builder().baseUrl(baseUrl).addConverterFactory(jsonConverter)
        // create a Retrofit instance
        val retrofit = retrofitBuiler.build()
        // create our client
        myHttpClient = retrofit.create(Service::class.java)
    }

    interface RequestCallback {
        fun onChaptersReceived(chapters: ChapterJSONList)
        fun onError()
    }

    fun sendRequest(callback: RequestCallback) {
        val myHttpCall: Call<ChapterJSONList> = myHttpClient.getChapters()
        val myCallback: Callback<ChapterJSONList> = object : Callback<ChapterJSONList> {
            override fun onResponse(call: Call<ChapterJSONList>, response: Response<ChapterJSONList>) {
                Log.i("HTTPS", "SUCCESS")
                val chapters = response.body()
                if (chapters != null) {
                    callback.onChaptersReceived(chapters)
                } else {
                    callback.onError()
                }
            }

            override fun onFailure(call: Call<ChapterJSONList>, t: Throwable) {
                Log.i("HTTPS", "FAILLURE")
                callback.onError()
            }
        }
        myHttpCall.enqueue(myCallback)
    }


    interface RequestVersesCallback {
        fun onVerseReceived(verses: VerseJSONList)
        fun onError()
    }


    fun sendRequestVerseByChapterId(idChapter : Int, pageNumber : Int, callback: RequestVersesCallback) {
        val myHttpCall: Call<VerseJSONList> = myHttpClient.getVersesByChapterId(idChapter,pageNumber)
        val myCallback: Callback<VerseJSONList> = object : Callback<VerseJSONList> {
            override fun onResponse(call: Call<VerseJSONList>, response: Response<VerseJSONList>) {
                Log.i("HTTPS", "SUCCESS")
                val verses = response.body()
                if (verses != null) {
                    callback.onVerseReceived(verses)
                } else {
                    callback.onError()
                }
            }

            override fun onFailure(call: Call<VerseJSONList>, t: Throwable) {
                Log.i("HTTPS", "FAILLURE")
                callback.onError()
            }
        }
        myHttpCall.enqueue(myCallback)
    }

    interface RequestChapterCallback {
        fun onChapterReceived(chapter: ChapterResponse)
        fun onError()
    }

    fun sendRequestChapterById(idChapter: Int, callback: RequestChapterCallback) {
        val myHttpCall: Call<ChapterResponse> = myHttpClient.getChapterById(idChapter)
        val myCallback: Callback<ChapterResponse> = object : Callback<ChapterResponse> {
            override fun onResponse(call: Call<ChapterResponse>, response: Response<ChapterResponse>) {
                Log.i("HTTPS", "SUCCESS")
                val chapterResponse = response.body()
                if (chapterResponse != null) {
//                    val chapter = chapterResponse.chapter
                    callback.onChapterReceived(chapterResponse)
                } else {
                    callback.onError()
                }
            }

            override fun onFailure(call: Call<ChapterResponse>, t: Throwable) {
                Log.i("HTTPS", "FAILURE")
                callback.onError()
            }
        }
        myHttpCall.enqueue(myCallback)
    }

    interface RequestChapterInfosCallback {
        fun onChapterInfosReceived(chapter: ChapterInfoResponse)
        fun onError()
    }

    fun sendRequestChapterInfosById(idChapter: Int, callback: RequestChapterInfosCallback) {
        val myHttpCall: Call<ChapterInfoResponse> = myHttpClient.getChapterInfoById(idChapter)
        val myCallback: Callback<ChapterInfoResponse> = object : Callback<ChapterInfoResponse> {
            override fun onResponse(call: Call<ChapterInfoResponse>, response: Response<ChapterInfoResponse>) {
                Log.i("HTTPS", " sendRequestChapterInfosById SUCCESS")

                val chapterInfoReponse = response.body()
                if (chapterInfoReponse != null) {
                    callback.onChapterInfosReceived(chapterInfoReponse)
                } else {
                    callback.onError()
                }
            }

            override fun onFailure(call: Call<ChapterInfoResponse>, t: Throwable) {
                Log.i("HTTPS", "FAILURE")
                callback.onError()
            }
        }
        myHttpCall.enqueue(myCallback)
    }


}