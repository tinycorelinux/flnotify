/*
	FLTK notify applet

	(C) Curaga
*/

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/x.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 280
#define H 120
#define COMMAND "ps -e | grep -v grep | grep -c flnotify"
#define VER "0.9.2"

static void timeout(void *) {
	exit(0);
}

class mybox: public Fl_Box {
public:
	mybox(int x, int y, int w, int h, const char *lbl): Fl_Box(x, y, w, h, lbl) {}

	int handle(int event) {
		if (event == FL_PUSH)
			timeout(NULL);

		return 0;
	}
};

static int parser(int, char **, int &) {

	return 0;		// gets rid of FLTK help text.
}

int main(int argc, char **argv) {

	float time = 5;
	int i = 0, t = 0, b = 0, hpos = 0, wpos = 0;
	FILE *pipe;
	Fl::args(argc, argv, i, &parser);

	if (argc == 1 || strcmp(argv[1], "--help") == 0
	    || strcmp(argv[1], "-h") == 0) {

		printf("\nflnotify v%s\n\n"
			"Usage: %s [opts] \"say hi\"\n\n"

		       "Options:\n\n"
		       "\t-t [time to show] default 5.0\n\n"
		       "Colors:\n"
		       "\t-bg <color> background color\n"
		       "\t-fg <color> text color\n\n"

		       "The color can be either named (green) or rgb ('#00ff00').\n\n"
		       "Position:\n"
		       "\t-r right\n"
		       "\t-b bottom (left by default, right with -r)\n"
		       "\t-c center\n\n"
		       "For anywhere else, use the standard -g option.\n"
		       "The size can also be changed with -g.\n", VER, argv[0]);

		return 0;
	}

// First check if something is already being notified. If so, position somewhere else.

	pipe = popen(COMMAND, "r");
	if (fscanf(pipe, "%d", &t) != 1)
		exit(1);
	pclose(pipe);

// Parse command line

	for (i = argc - 2; i; i--) {	// first and last need no check
		if (strcmp(argv[i], "-t") == 0)
			time = atof(argv[i + 1]);
		else if (strcmp(argv[i], "-r") == 0)
			wpos = Fl::w() - W;
		else if (strcmp(argv[i], "-b") == 0) {
			hpos = Fl::h() - H;
			b = 1;
			if (t > 1)
				hpos -= (H * (t - 1));
		} else if (strcmp(argv[i], "-c") == 0) {
			wpos = (Fl::w() - W) / 2;
			hpos = (Fl::h() - H) / 2;
		}
	}
	if (t > 1 && !b)
		hpos += (H * (t - 1));	// If not at bottom, we position below

// Drawing

	Fl_Window *window = new Fl_Window(wpos, hpos, W, H);
	window->border(0);
	window->box(FL_NO_BOX);

	mybox *box = new mybox(2, 2, W - 4, H - 4, argv[argc - 1]);
	box->box(FL_UP_BOX);
	box->align(FL_ALIGN_WRAP);

	window->end();
	window->set_override();

	window->show(argc, argv);

	Fl::add_timeout(time, timeout, NULL);
	return Fl::run();
}
