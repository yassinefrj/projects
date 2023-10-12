<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class CaptchaServiceController extends Controller
{
    /**
     * Reload the captcha image.
     * This method reloads the captcha image by generating a new captcha and returning the image URL.
     *
     * @return \Illuminate\Http\JsonResponse
     *     Returns a JSON response containing the new captcha image URL.
     */
    public function reloadCaptcha()
    {
        return response()->json(['captcha'=> captcha_img()]);
    }
}
