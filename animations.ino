void Gouttes()
{
    debut();
    for(int j = 0; j < 5; j++) {
    int compteur = 10;
    for(int i=0;i<60;i++)
    {
        int i1 = compteur;
        int i2 = 128;
        for(int i=0;i<9;i++)
        {
            allumer(i1,i2,i2,i2);
            i2 = (i2) / (2);
            i1 += -1;
        }
        compteur += 1;
        delay(10);
    }
    }
}


static void retrecir(int position)
{
    int i1, i2;
    i1 = 0;
    
    for(int i=0;i<9;i++)
    {
        i2 = (i1) + (position);
        allumer(i2,0);
        i1 += 1;
        for(int i=0;i<(10) - (i1);i++)
        {
            i2 += 1;
            allumer(i2,((10) - (i1)) * (6));
        }
        delay(1000*0.1);
    }
    
}

static void grandir(int position)
{
    int i1, i2;
    i1 = 1;
    
    for(int i=0;i<10;i++)
    {
        i2 = position;
        for(int i=0;i<i1;i++)
        {
            allumer(i2,(i1) * (6));
            i2 += 1;
        }
        i1 += 1;
        delay(1000*0.1);
    }
    
}

void Chenille() {
	    int compteur = 1;
	    debut();
	    for(int i=0;i<6;i++)
	    {
	        grandir(compteur);
	        retrecir(compteur);
	        compteur += 9;
	    }
}
void Suzie() {
	    int compteur = 1;
	    for(int i=0;i<3;i++)
	    {
	        compteur = 11;
	        while(!((compteur) > (200)))
	        {
	            delay(1000*0.02);
	            allumer(0,compteur);
	            compteur += 10;
	        }
	    }
}

void Laissa() {
	    int compteur = 1;
	    while(!((compteur) > (200)))
	    {
	        allumer(0,compteur);
	        compteur += 2;
	        delay(1000*0.02);
	    }


}

void Phare() {
	    int compteur = 1, i1, i2;
	    for(int i=0;i<3;i++)
	    {
	        int couleur = random(1,200);
	        i1 = 30;
	        for(int i=0;i<30;i++)
	        {
	            allumer(i1,couleur);
	            i1 += -1;
	            delay(1000*0.02);
	        }
	        i1 = 1;
	        for(int i=0;i<30;i++)
	        {
	            allumer(i1,0);
	            i1 += 1;
	            delay(1000*0.02);
	        }
	        i2 = 31;
	        for(int i=0;i<30;i++)
	        {
	            allumer(i2,couleur);
	            i2 += 1;
	            delay(1000*0.02);
	        }
	        i2 = 60;
	        for(int i=0;i<30;i++)
	        {
	            allumer(i2,0);
	            i2 += -1;
	            delay(1000*0.02);
	        }
	    }
}

void animation(int couleur)
{
    delay(1000*0.5);
    
    allumer(30,couleur);
    
    int c = 1;
    
    for(int i=0;i<30;i++)
    {
        allumer((30) + (c),couleur);
        allumer((30) - (c),couleur);
        c += 1;
        delay(1000*0.02);
    }
    
}

void Antoine() {
	    // Antoine
	    animation(133);
	    animation(1);
	    animation(66);
	    animation(100);
	    animation(166);
}

void Alice2() {
	    int compteur = 1, _l, couleur;
	    for(int i=0;i<5;i++)
	    {
	        couleur = random(1,200);
	        _l = 1;
	        for(int i=0;i<60;i++)
	        {
	            allumer(_l,couleur);
	            _l += 1;
	            delay(1000*0.02);
	        }
	        _l = 1;
	        for(int i=0;i<60;i++)
	        {
	            allumer(_l,0);
	            _l += 1;
	            delay(1000*0.02);
	        }
	        _l = 60;
	        for(int i=0;i<60;i++)
	        {
	            allumer(_l,couleur);
	            _l += -1;
	            delay(1000*0.02);
	        }
	        _l = 60;
	        for(int i=0;i<60;i++)
	        {
	            allumer(_l,0);
	            _l += -1;
	            delay(1000*0.02);
	        }
	    }
}
void Alice1() {
	    int compteur = 1, _l, couleur;
	    for(int i=0;i<5;i++)
	    {
	        couleur = random(1,200);
	        _l = 1;
	        for(int i=0;i<30;i++)
	        {
	            allumer(_l,couleur);
	            _l += 2;
	            delay(1000*0.02);
	        }
	        _l = 60;
	        for(int i=0;i<30;i++)
	        {
	            allumer(_l,couleur);
	            _l += -2;
	            delay(1000*0.02);
	        }
	        _l = 1;
	        for(int i=0;i<30;i++)
	        {
	            allumer(_l,0);
	            _l += 2;
	            delay(1000*0.02);
	        }
	        _l = 60;
	        for(int i=0;i<30;i++)
	        {
	            allumer(_l,0);
	            _l += -2;
	            delay(1000*0.02);
	        }
	    }

}
