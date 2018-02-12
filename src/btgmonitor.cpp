#include "include/btgmonitor.h"

bool isRunning();
int binping();
int gateping();
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}

void update()
{
//   ifstream inf("/var/www/html/bitg/index.html");
//   ofstream outf("/var/www/html/bitg/index.html");

   for(;;)
   {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        char command[128];
	if(isRunning())
	{
	system("rpl -i -q --quiet '<!-- Status -->Bitgrinder status:  <font color=\"red\">Offline</font>\' '<!-- Status -->Bitgrinder status:  <font color=\"green\">Online</font>\' /var/www/html/bitg/index.html > /dev/null 2>&1");
	//sprintf(command, "rpl -i -q -w '%s %s %s' '' /var/www/html/bitg/index.html", gateping(), binping(), "---");
	sprintf(command, "sed -i '/<!--- Ping.*/c\\<!-- Ping -->Gate.io:  %g	Binance:  %b	Cryptopia:  --- ' /var/www/html/bitg/index.html", gateping(), binping());
//sed 's/^<!---.*/No Comment/' test > test

	//sprintf(command, "sed 's/^<!--- Ping.*/<!-- Ping -->Gate.io:  %g  Binance/:  %b    Cryptopia:  --- ' /var/www/html/bitg/index.html", gateping(), binping());
	system(command);
	//<!-- Status -->Bitgrinder status:  <font color="green">Online</font>
	  //std::cout<<"Running";
	} else {
	system("rpl -i -q --quiet '<!-- Status -->Bitgrinder status:  <font color=\"green\">Online</font>\' '<!-- Status -->Bitgrinder status:  <font color=\"red\">Offline</font>' /var/www/html/bitg/index.html > /dev/null 2>&1");
	//sprintf(command, "sed 's/<!--- Ping.*/<!-- Ping -->Gate.io:  %g	Binance:  %b	Cryptopia:  --- ' /var/www/html/bitg/index.html", gateping(), binping());
	sprintf(command, "sed -i '/<!--- Ping.*/c\\<!-- Ping -->Gate.io:  %g	Binance:  %b	Cryptopia:  --- ' /var/www/html/bitg/index.html", gateping(), binping());
	system(command);
	//system("rpl -i -q -w '' '' /var/www/html/bitg/index.html");
	//<!-- Status -->Bitgrinder status:  <font color="red">Offline</font>
	  //std::cout<<"Offline";
	}
        // <-- call your function here
   }
}

//bool isRunning(const char* name)  
bool isRunning()  
{  
   char command[32];  
   //sprintf(command, "pgrep %s > /dev/null", name);  
   sprintf(command, "pgrep %s > /dev/null", "bitgrinder");  
   return 0 == system(command);  
   //if(system(command)>0){return true;}else{return false;}
   //return system(command);  
} 

int gateping()
{

auto started = std::chrono::high_resolution_clock::now();
CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  //curl_easy_setopt (curl, CURLOPT_VERBOSE, 0L); //0 disable messages
  if(curl) {
    //curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v1/ping");
    curl_easy_setopt(curl, CURLOPT_URL, "https://data.gate.io/api2/1/ticker/eth_btc");
        //USING CURLOPT NOBODY
        curl_easy_setopt(curl, CURLOPT_NOBODY,1);
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  auto done = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count();

}

int binping()
{

auto started = std::chrono::high_resolution_clock::now();
CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  //curl_easy_setopt (curl, CURLOPT_VERBOSE, 0L); //0 disable messages
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v1/ping");
        //USING CURLOPT NOBODY
        curl_easy_setopt(curl, CURLOPT_NOBODY,1);    
//curl_easy_setopt(curl, CURLOPT_URL, "https://data.gate.io/api2/1/ticker/eos_eth");

#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  auto done = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count();
}

int main ( int argc, char *argv[] )
{
  std::thread(update).detach();
  for(;;)
  {

  }
  //std::string Temp;
  //std::cin >> Temp;
  return 0;
}
