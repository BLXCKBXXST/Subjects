#include <stdio.h>
#include <time.h>
#include "coursework.h"
#include "tree.h"
#include "preview.h"
#include "../../labs/lab-viewer.h"

int obnovit_prosmotr(struct Derevo *root, int otkrit) {
    static int browserOpened = 0;
    static unsigned long revision = 0;
    if (!sohranit_svg(root, SVG_FILE)) {
        perror(SVG_FILE);
        return 0;
    }
    if (!sohranit_zapisi_svg(root, "coursework/src/a2-records.svg")) {
        perror("coursework/src/a2-records.svg");
        return 0;
    }
    FILE *file = fopen(REVISION_FILE, "w");
    if (file == NULL) {
        perror(REVISION_FILE);
        return 0;
    }
    fprintf(file, "window.courseworkRevision = '%lu-%lu-%lu';\n",
            (unsigned long)time(NULL), (unsigned long)clock(), ++revision);
    if (fclose(file) != 0) {
        perror(REVISION_FILE);
        return 0;
    }
    if (otkrit && !browserOpened)
        browserOpened = openLabPage(PREVIEW_FILE);
    return 1;
}
