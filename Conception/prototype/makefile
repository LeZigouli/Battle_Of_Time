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
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC := $(BINDIR)/$(TARGET)
rm = rm -f

################
#--Programme--#
################
#Édition des liens
$(EXEC) : $(OBJECTS)
	@$(LINKER) $(OBJECTS) -L$(LIBDIR) -o $@  $(LFLAGS)
	@echo "Édition de liens terminée!"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(LIBDIR)
	@$(CC) $(CFLAGS) -I$(LIBDIR) -c $< -o $@
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