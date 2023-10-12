package com.example.project.database

import androidx.room.Entity
import androidx.room.PrimaryKey
import com.squareup.moshi.Json


data class ChapterJSONList(
    val chapters: List<ChapterJSON>
)


@Entity(tableName = "chapter_list")
data class ChapterJSON(
    @PrimaryKey
    @Json(name = "id")
    val id: Int,
    @Json(name = "name_simple")
    val name_simple: String,
    var count: Int = 0,
    var isDownloaded: Boolean = false,
    var pathInLocal: String? = ""
)

data class VerseJSONList(
    val verses: List<Verse>
)

data class Verse(
    val id: Int,
    val verse_number: Int,
    val verse_key: String,
    val hizb_number: Int,
    val rub_el_hizb_number: Int,
    val ruku_number: Int,
    val manzil_number: Int,
    val sajdah_number: Int?,
    val page_number: Int,
    val juz_number: Int,
    val words: List<Word>
)

data class Word(
    val id: Int,
    val position: Int,
    val audio_url: String?,
    val char_type_name: String,
    val code_v1: String,
    val page_number: Int,
    val line_number: Int,
    val text: String,
    val translation: Translation,
    val transliteration: Transliteration
)

data class Translation(
    val text: String,
    val language_name: String
)

data class Transliteration(
    val text: String,
    val language_name: String
)


data class ChapterResponse(
    val chapter: ChapterJSONVerse
)

data class ChapterJSONVerse(
    val id: Int,
    val revelation_place: String,
    val revelation_order: Int,
    val bismillah_pre: Boolean,
    val name_simple: String,
    val name_complex: String,
    val name_arabic: String,
    val verses_count: Int,
    val pages: List<Int>
)

data class ChapterInfoResponse(
    val chapter_info: ChapterInfo
)

data class ChapterInfo(
    val id: Int,
    val chapter_id: Int,
    val language_name: String,
    val short_text: String,
    val source: String?,
    val text: String
)


