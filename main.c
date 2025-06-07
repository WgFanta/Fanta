#include <gtk/gtk.h>

char current = 'X';
GtkWidget *buttons[3][3];

int check_win() {
    // Проверка строк, столбцов и диагоналей на победу
    for (int i = 0; i < 3; i++) {
        // Проверка строк
        if (gtk_button_get_label(GTK_BUTTON(buttons[i][0]))[0] != ' ' &&
            gtk_button_get_label(GTK_BUTTON(buttons[i][0]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[i][1]))[0] &&
            gtk_button_get_label(GTK_BUTTON(buttons[i][1]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[i][2]))[0])
            return 1;
        // Проверка столбцов
        if (gtk_button_get_label(GTK_BUTTON(buttons[0][i]))[0] != ' ' &&
            gtk_button_get_label(GTK_BUTTON(buttons[0][i]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[1][i]))[0] &&
            gtk_button_get_label(GTK_BUTTON(buttons[1][i]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[2][i]))[0])
            return 1;
    }
    // Диагонали
    if (gtk_button_get_label(GTK_BUTTON(buttons[0][0]))[0] != ' ' &&
        gtk_button_get_label(GTK_BUTTON(buttons[0][0]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[1][1]))[0] &&
        gtk_button_get_label(GTK_BUTTON(buttons[1][1]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[2][2]))[0])
        return 1;
    if (gtk_button_get_label(GTK_BUTTON(buttons[0][2]))[0] != ' ' &&
        gtk_button_get_label(GTK_BUTTON(buttons[0][2]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[1][1]))[0] &&
        gtk_button_get_label(GTK_BUTTON(buttons[1][1]))[0] == gtk_button_get_label(GTK_BUTTON(buttons[2][0]))[0])
        return 1;

    return 0;
}

int check_draw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (gtk_button_get_label(GTK_BUTTON(buttons[i][j]))[0] == ' ')
                return 0;
    return 1;
}

void on_button_clicked(GtkButton *button, gpointer user_data) {
    if (gtk_button_get_label(button)[0] == ' ') {
        gtk_button_set_label(button, (current == 'X') ? "X" : "O");
        if (check_win()) {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                       "Победил игрок %c!", (current == 'X') ? 'X' : 'O');
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            // Сбросить поле
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    gtk_button_set_label(GTK_BUTTON(buttons[i][j]), " ");
        } else if (check_draw()) {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                       "Ничья!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    gtk_button_set_label(GTK_BUTTON(buttons[i][j]), " ");
        } else {
            current = (current == 'X') ? 'O' : 'X';
        }
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Крестики-нолики");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buttons[i][j] = gtk_button_new_with_label(" ");
            gtk_widget_set_size_request(buttons[i][j], 60, 60);
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(on_button_clicked), NULL);
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j, i, 1, 1);
        }
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

