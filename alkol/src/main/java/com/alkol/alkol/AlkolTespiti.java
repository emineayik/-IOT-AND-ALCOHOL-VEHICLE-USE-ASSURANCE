package com.alkol.alkol;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/tespit")
public class AlkolTespiti {

    //@ResponseStatus(HttpStatus.OK)
    @RequestMapping(method = RequestMethod.POST, value = "/{yuz}/{alkol_orani}")
    @ResponseBody
    public int getTespit(@PathVariable int yuz, @PathVariable int alkol_orani) {
        ApiYanitlari apiYanitlari = new ApiYanitlari();
        int alkol_siniri = 50; //alkol sinirini belirledik
        boolean yuz_tanima = true; //yuz tanima degeri belirledik
        if (yuz > 5) {
            yuz_tanima = true;
        } else {
            yuz_tanima = false;
        }
        if (alkol_orani < alkol_siniri && yuz_tanima == true) { //elimizde bulunan ihtimallerin if donguleri
            return apiYanitlari.alkolsuzTanitilmis; //baska class tan sabiti cagirdik
        } else if (alkol_orani > alkol_siniri && yuz_tanima == false) {
            return apiYanitlari.alkolluTanitilmamis;
        } else if (alkol_orani < alkol_siniri && yuz_tanima == false) {
            return apiYanitlari.alkolsuzTanilmamis;
        } else if (alkol_orani > alkol_siniri && yuz_tanima == true) {
            return apiYanitlari.alkolluTanitilmis;
        } else {
            return apiYanitlari.bilinmeyenDurum;
        }

    }

    public static boolean gps() {//alkol kullanimi var ise kontrolu
        return true;
    }

    public static void gps_konum() { //aracin hareket etmesini ayri bir fonksiyonda yazdik kod tekrari olmasin diye
        if (gps() == true) {
            System.out.println("arac haret ediyor");
        } else {
            System.out.println("alkollu arac kullanimi yok");

        }
    }
}
