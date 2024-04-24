include makefile.compilation

#Makefile générique avec SDL2

############
#--Macros--#
############
#Nom des répertoires
SRCDIR = src
BINDIR = bin
OBJDIR = obj
LIBDIR = lib
SAVEDIR = save
SOCKETDIR = socket

#Appel pour la création des dossiers
DIRS = $(OBJDIR) $(BINDIR)

.PHONY: DIRS
all: $(DIRS) $(OBJDIR)/serveur.o $(OBJDIR)/client.o $(BINDIR)/$(TARGET)

#Création des dossiers
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(SAVEDIR):
	mkdir -p $(SAVEDIR)

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC := $(BINDIR)/$(TARGET)
rm = rm -f

################
#--Programme--#
################
#Édition des liens
$(EXEC) : $(OBJECTS) $(OBJDIR)/client.o $(OBJDIR)/serveur.o
	@$(LINKER) $(OBJECTS) $(OBJDIR)/client.o $(OBJDIR)/serveur.o -L$(LIBDIR) -o $@  $(LFLAGS)
	@echo "Édition de liens terminée!"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(LIBDIR)
	@$(CC) $(CFLAGS) -I$(LIBDIR) -c $< -o $@
	@echo "Compilation "$<" réussie!"

# POUR LE SOCKET
$(OBJDIR)/client.o : $(SOCKETDIR)/client.c $(SOCKETDIR)/client.h
	@$(CC) -c $< -o $@

$(OBJDIR)/serveur.o : $(SOCKETDIR)/serveur.c $(SOCKETDIR)/serveur.h
	@$(CC) -c $< -o $@

#################
#--Utilitaires--#
#################
#Supprime les fichiers intermidiaires (objets)
.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@echo "Fichiers objets effacés!"

#clean + supprime l'exécutable
.PHONY: mrproper
mrproper: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Exécutable effacé"
