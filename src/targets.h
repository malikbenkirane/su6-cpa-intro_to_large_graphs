#ifdef PPTI

/**
 * on any computer at ssh.ufr-info-p6.jussieu.fr (ppti-14-*room-*computer)
 */
#ifdef FRIENDSTER
#define FILENAME "/users/nfs/Vrac/TME_CPA_19-02-20/com-friendster.ungraph.txt"
#elif LJ
#define FILENAME "/users/nfs/Vrac/TME_CPA_19-02-20/com-lj.ungraph-clean.txt"
#elif ORKUT
#define FILENAME "/users/nfs/Vrac/TME_CPA_19-02-20/com-orkut.ungraph-clean.txt"
#elif AMAZON
#define FILENAME "/users/nfs/Vrac/TME_CPA_19-02-20/com-amazon.ungraph-clean.txt"
#elif EMAIL
#define FILENAME "/users/nfs/Vrac/TME_CPA_19-02-20/email-Eu-core-clean.txt"
#endif

#elif LOCAL 
/**
 * To change accordingly to local files path.
 * To download from : 
 * - http://snap.stanford.edu/data/email-Eu-core.html
 * - http://snap.stanford.edu/data/com-Amazon.html
 * - http://snap.stanford.edu/data/com-LiveJournal.html 
 * - http://snap.stanford.edu/data/com-Orkut.html
 * - http://snap.stanford.edu/data/com-Friendster.html
 * Then to clean with clean.sh script.
 */
#ifdef FRIENDSTER
#error unavailable
#elif LJ
#define FILENAME "../assets/clean/com-lj.ungraph.txt"
#elif ORKUT
#define FILENAME "../assets/clean/com-orkut.ungraph.txt"
#elif AMAZON
#define FILENAME "../assets/clean/com-amazon.ungraph.txt"
#elif EMAIL
#define FILENAME "../assets/clean/email-Eu-core.txt"
#endif

#endif
