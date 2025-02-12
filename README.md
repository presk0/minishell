to do:
Retour d'evaluation:

 pour : cd not_existant_file comprortement etrange de cat cat ls mais reste OK les variable d'evironement non executer ne sont pas retirer de la commande : echo $no_existant_var printera "$no_existant_var" en cas de redirection qui veullent envoyer dans un fichier qui n'a pas les perms ou une directory, le retour sera pour ls > no_perms_file perrmision denied et le resultat du ls

Les messages d'erreurs manquent beaucoup a l'appel, l'update de $? ne fonctionne pas tres bien mais l'erreur est reconnue est resolvable facilement. Quelques petits details tel que export une variable sans valeur n'ont pas ete implementes, la gestion des pipes n'est pas exacte, chaque processus attend independamment. J'ai du invalider les redirections car un test explicitement donne ne passe pas.

wait_pid devrait attendre tous les processus,
exit renvoit un mauvais message d'erreur dans ds conditions normales (ne devrait pas etre modifie si < 128)
builtins fait a la va-vite (ne considere pas les erreurs)
Le retour d'erreur revoit l'erreur de la commande et ne considere pas les erreurs du au bash (ex: bash ou redirections problematique) -> devrait gerer le retour d'erreur plus largement que renvoyer le retour d'erreur du programme appele
La gestion de la fermeture des quotes est de trop

