############
#--Macros--#
############

#Nom du projet
TARGET = exe
#Compilateur utilisé
CC = gcc
#Option de compilation
CFLAGS = -Wall -I.
#Éditeur de liens
LINKER = gcc
#Option de l'éditeur de liens
LFLAGS = -Wall -I.

#Nom des répertoires
SRCDIR = src
BINDIR = bin
OBJDIR = obj
LIBDIR = lib

#Appel pour la création des dossiers
DIRS = $(OBJDIR) $(BINDIR)

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

#Création des dossiers
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)


SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm = rm -f

################
#--Programme--#
################
#Édition des liens
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Édition de liens terminée!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilation "$<" réussie!"

#################
#--Utilitaires--#
#################

#Supprime les fichiers intermidiaires (objets)
.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Fichiers objets effacés!"


#clean + supprime l'exécutable
.PHONY: mrproper
mrproper: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Exécutable effacé"