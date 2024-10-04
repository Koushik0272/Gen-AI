import pyttsx3
import speech_recognition as sr
import datetime
import wikipedia
import webbrowser
import os
import smtplib
engine = pyttsx3.init('sapi5')
voice = engine.getProperty('voice')
# print(voices[1].id)
engine.setProperty('voice', voices[0].id)
class ShakthiAssistant:
    def __init__(self):
        # Initialize speech engine
        self.engine = pyttsx3.init()

    def speak(self, audio):
        self.engine.say(audio)
        self.engine.runAndWait()

    def wishMe(self):
        hour = int(datetime.datetime.now().hour)
        if hour >= 0 and hour < 12:
            print("Good Morning!")
            self.speak("Good Morning!")
        elif hour >= 12 and hour < 18:
            print("Good Afternoon!")
            self.speak("Good Afternoon!")
        else:
            print("Good Evening!")
            self.speak("Good Evening!")
        print("I am Shakthi Sir. Please tell me how may I help you")    
        self.speak("I am Shakthi Sir. Please tell me how may I help you")

    def takeCommand(self):
        # It takes microphone input from the user and returns string output
        r = sr.Recognizer()
        with sr.Microphone() as source:
            print("Listening...")
            r.pause_threshold = 0.5
            audio = r.listen(source)

        try:
            print("Recognizing...")
            query = r.recognize_google(audio, language='en-in')
            print(f"User said: {query}\n")
        except Exception as e:
            print("Say that again please...")
            return "None"
        return query

    def run(self):
        self.wishMe()
        while True:
            query = self.takeCommand().lower()

            # Logic for executing tasks based on query
            if 'wikipedia' in query:
                self.speak('Searching Wikipedia...')
                query = query.replace("wikipedia", "")
                results = wikipedia.summary(query, sentences=2)
                self.speak("According to Wikipedia")
                print(results)
                self.speak(results)

            elif 'open youtube' in query:
                webbrowser.open("youtube.com")

            elif 'open google' in query:
                webbrowser.open("google.com")

            elif 'open stack overflow' in query:
                webbrowser.open("stackoverflow.com")

            elif 'play music' in query:
                music_dir = 'https://open.spotify.com/playlist/0lkUhgbqXfuverFw3CznN3?si=8eb0f7054bd54077'
                songs = os.listdir(music_dir)
                print(songs)
                os.startfile(os.path.join(music_dir, songs[0]))

            elif 'the time' in query or 'what is the time' in query:
                strTime = datetime.datetime.now().strftime("%H:%M:%S")
                self.speak(f"Sir, the time is {strTime}")

            elif 'who am i' in query:
                self.speak("You are Koushik")

            elif 'who is my best friend' in query:
                self.speak("Koushik is your best friend")

            elif 'who are you' in query:
                
                self.speak("I am shakthi Sir, your personal assistant")

            elif 'open dev c' in query:
                os.startfile('C:\\Program Files (x86)\\Dev-Cpp\\devcpp.exe')

            elif 'email to koushik' in query:
                try:
                    self.speak("What should I say?")
                    content = self.takeCommand()
                    to = "koushikmunnaluri@gmail.com"
                    self.sendEmail(to, content)
                    self.speak("Email has been sent!")
                except Exception as e:
                    print(e)
                    self.speak("Sorry Anupam. I am not able to send this email")

# Create instance of ShakthiAssistant and run
if __name__ == "__main__":
    assistant = ShakthiAssistant()
    assistant.run()
