Προσωπικά στοιχεία:

Όνομα: Νικόλαος\
Επώνυμο: Πνευματικός

--------------------------------------------------------------------------------------------

Μέθοδος μεταγλώτισης: javac schoolSimulation.java\
εκτέλεση: java schoolSimulation 2 1 2 3 7 

--------------------------------------------------------------------------------------------


Οι περισσοτερες λειτουργιες ειναι ίδιες με την Ασκηση3. Το διαφορετικο ειναι οτι δεν υπαρχουν πλέον pointer στα αντικειμενα λόγο χρήσης java. Επισης εχουν προσθεθει και οι κατάλληλες συναρτήσεις για να υλοποίηθει η empty συνάρτηση που ζητείται από την άσκηση. Η empty συνάρτηση για κάθε όροφο πέρνει έναν-έναν μαθητή απο κάθε τάξει και τον βγάζει απο αυτην. Ο μαθητής μπαίνει στον διάδρομο οπου βγαίνει από αυτόν και από τον όροφο για να μπει στο κλιμακοστάσιο. Μετά βγαίνει από το κλιμακοστάσιο και μπαίνει στο προαύλιο. Τελος βγαίνει από το προαύλιο δηλαδή βγαίνει απο το σχολείο. Αυτο γίνεται μεχρι να αδειάσουν όλες η αιθουσες του ορόφου. Οταν γίνεται αύτο προχωράει στον επόμενο οροφο και επαναλαμβάνει την ίδια διαδικασία. μόλις βγούνε όλοι οι μαθητές απο το σχολείο τοτε τρέχει για άλλη μια φορά τους ορόφους και βγάζει όλους τουσ καθηγητές από τις τάξεις τους, δηλαδη από το σχολείο.

--------------------------------------------------------------------------------------------

Στο αρχείο schoolSimulation.java οπού αναπαριστάνει την μέιν έχω κάνει import το java.io ωστε να μπορώ να ορίσω μεταβλητές τύπου file και BufferedReader. Η file θα ανοίξει δυο αρχεια, το teachers.txt και students.txt. Με το bufferreader θα ξεχωρίζω τισ γραμμες απο κάθε αρχείο και ετσι μπορω για κάθε γραμμη να καλώ την teachreg και studreg αντίστοιχα ώστε να καταγράφονται καθηγητές και μαθητές στο σχολείο καθώς και σε ποια τάξη θα ανήκουν. 

Μετά καλείται η simulation η οποία τοποθετεί με τυχαία σειρά τους μαθητές στο σχολείο, και για καθέναν από αυτούς τους τοποθετεί στις τάξεις τους. Μετά τοποθετεί και τους καθηγητές πάλι με τυχαία σειρά στην τάξη τους.

Μετά την κλήση της simulation καλείται η attend η οποία για τις ώρες λειτουργίας του σχολείου αυξάνει τον βαθμό κούρασης τον μαθητών και καθηγητών.

Μετά καλείται η print η οποία εκτυπώνει τους μαθητές και καθηγητές που βρίσκονται σε κάθε αίθουσα καθώς και τον βαθμό κούρασής τους.    

Τέλος καλείται η empty η οποία αφαιρεί τους μαθητές και τους καθηγητές απο τις τάξεις τους και τους βγάζει από το σχολείο.