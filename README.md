com.webos.service.ai
====================

Summary
-------
Ai service for webOS OSE

Description
-----------
This service provides ai features such as speech/face/gesture recognition.

API summary
-----------
webOS OSE provides methods only for speech recognition yet.

1. Start the service
$ luna-send -n 1 -f luna://com.webos.service.ai.voice/start '{"mode":"continuous", "keywordDetect":true}'
  {
      "returnValue": true
  }

  Parameters
  * mode: 'continuous' or 'single'. Continuous menas the service will restart when recognition finished.
  * keywordDetect: true' or false. For using keyword activation such as 'Ok,Google'

2. Stop
$ luna-send -n 1 -f luna://com.webos.service.ai.voice/stop '{}'
  {
      "returnValue": true
  }

3. getState
$ luna-send -i -f luna://com.webos.service.ai.voice/getState '{"subscribe":true}'
  {
      "returnValue": true
      "state": "idle"
  }

  Life cycle of the service is state machine.
  * idle          : before start.
  * waitActivation: wait for keyword activation.
  * recording     : connect NLP server and uploading audio for speech recognition.
  * thinking      : wait for results of speech recognition.
  * answering     : answering to requests via speaker.
  
          [start]                        [keyword detected]
  idle -------------------------> waitActivation ----> recording --> thinking --> answering
   ^    | (keywordDetect: true)                           ^                          |
   |    |                                                 |                          |
   |    ---------------------------------------------------                          |
   |    ^ (keywordDetect: false)                                                     |
   |    |                                                                            |
   -----------------------------------------------------------------------------------
          (mode: continuous) 


4. getResponse
$ luna-send -i -f luna://com.webos.service.ai.voice/getResponse '{"subscribe":true}'

  The default keyword is "snowboy", So just say "snowboy! what's the weather?"
  (You can change the keyword model, refer to the (https://snowboy.kitt.ai/) and [ai.env] file)

  {
      "provider": "googleassistant",
      "response": {
          "keywordDetected": 1
      }
  }
  {
      "provider": "googleassistant",
      "response": {
          "partial": "what's the"
      }
  }
  {
      "provider": "googleassistant",
      "response": {
          "partial": "what's the weather"
      }
  }
  {
      "provider": "googleassistant",
      "response": {
          "displayText": "Cloudy with a chance of clouds! Currently in Seoul it's 79 and cloudy. The forecast today is 77 and cloudy. ( More on weather.com )"
      }
  }
