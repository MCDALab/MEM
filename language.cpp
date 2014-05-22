#include "language.h"

Language * Language::inst = NULL;
QHash<QString, QString> Language::languageMap;
QString Language::actual_lang = QString::null;

Language::Language()
{
}

Language * Language::instance()
{
    if( !inst )
        inst = new Language;
    return inst;
}

void Language::loadLanguage(QString lang)
{
    actual_lang = lang;
    if( lang == "pt-BR" )
    {
        languageMap["open"]= QString::fromLatin1("Abrir");
        languageMap["edit"]= QString::fromLatin1("Editar");
        languageMap["new"]= QString::fromLatin1("Novo");
        languageMap["configuration"]= QString::fromLatin1("Configuração");
        languageMap["title"]= QString::fromLatin1("MEM - Multiplex Electionis Methodus");
        languageMap["title_graphic_sensibility"]= QString::fromLatin1("Gráfico de sensibilidade");
        languageMap["add_criteria_title"]= QString::fromLatin1("Adicionar critério");
        languageMap["add_alternative_title"]= QString::fromLatin1("Adicionar alternativa");
        languageMap["save"]= QString::fromLatin1("Salvar");
        languageMap["save_as"]= QString::fromLatin1("Salvar como...");
        languageMap["save_new_file_MEM"]= QString::fromLatin1("Deseja salvar um novo arquivo MEM");
        languageMap["close"]= QString::fromLatin1("Fechar");
        languageMap["english"]= QString::fromLatin1("Inglês");
        languageMap["portuguese"]= QString::fromLatin1("Português");
        languageMap["matrix_payment"]= QString::fromLatin1("Matriz de pagamento");
        languageMap["matrix_weight"]= QString::fromLatin1("Matriz de pesos");
        languageMap["matrix_relationship"]= QString::fromLatin1("Matriz de complementariedade");
        languageMap["files"]= QString::fromLatin1("Arquivos");
        languageMap["recent_files"]= QString::fromLatin1("Arquivos recentes");
        languageMap["language"]= QString::fromLatin1("Idioma");
        languageMap["name_criteria"]= QString::fromLatin1("Nome do critério");
        languageMap["name_alternative"]= QString::fromLatin1("Nome da alternativa");
        languageMap["add"]= QString::fromLatin1("Adicionar");
        languageMap["cancel"]= QString::fromLatin1("Cancelar");
        languageMap["message_null_value_criteria"]= QString::fromLatin1("O valor do critério não pode ser nulo.");
        languageMap["message_null_value_alternative"]= QString::fromLatin1("O valor da alternativa não pode ser nulo.");
        languageMap["message_existing_criteria"]= QString::fromLatin1("Este nome de critério já existe, favor escolher outro nome.");
        languageMap["message_existing_alternative"]= QString::fromLatin1("Este nome de alternativa já existe, favor escolher outro nome.");
        languageMap["mirroring"]= QString::fromLatin1("Espelhamento");
        languageMap["preference"]= QString::fromLatin1("Preferência");
        languageMap["preferences"]= QString::fromLatin1("Preferências");
        languageMap["growing"]= QString::fromLatin1("Crescente");
        languageMap["decreasing"]= QString::fromLatin1("Decrescente");
        languageMap["weight"]= QString::fromLatin1("Peso");
        languageMap["weights"]= QString::fromLatin1("Pesos");
        languageMap["about"]= QString::fromLatin1("Sobre");
        languageMap["help"]= QString::fromLatin1("Ajuda");
        languageMap["spanish"]= QString::fromLatin1("Espanhol");
        languageMap["franch"]= QString::fromLatin1("Francês");
        languageMap["matrix_a_line"]= QString::fromLatin1("Matriz A'");
        languageMap["matrix_b_line"]= QString::fromLatin1("Matriz B'");
        languageMap["apply"]= QString::fromLatin1("Aplicar");
        languageMap["precision"]= QString::fromLatin1("Precisão");
        languageMap["choices"]= QString::fromLatin1("Quantidade de escolhas");
        languageMap["title_information"]= QString::fromLatin1("Informação");
        languageMap["table_is_empty"]= QString::fromLatin1("A tabela de pagamento não pode estar vazia.");
        languageMap["table_is_small"]= QString::fromLatin1("A tabela de relacionamento é pequena demais.");
        languageMap["table_result_find_info"]= QString::fromLatin1("Resultado: %1 de %2 encontrado(s) para %3.");
        languageMap["table_result_not_found_info"]= QString::fromLatin1("Nenhum resultado encontrado para %1.");
        languageMap["none"]= QString::fromLatin1("Nenhum");
        languageMap["validate_alternative"]= QString::fromLatin1("Falta avaliar a alternativa %1 à luz do Critério %2");
        languageMap["validate_weight"]= QString::fromLatin1("Falta atribuir um peso ao critério %1");
        languageMap["validate_criteria"]= QString::fromLatin1("Falta avaliar a complementariedade entre os critérios %1 e %2.");
        languageMap["matrix_b"]= QString::fromLatin1("Matriz B");
        languageMap["result"]= QString::fromLatin1("Resultado");
        languageMap["graphics"]= QString::fromLatin1("Gráficos");
        languageMap["menu_sensibility_graphic"]= QString::fromLatin1("Gráfico de sensibilidade");
        languageMap["menu_graphic_performace"]= QString::fromLatin1("Desempenho de alternativa");
        languageMap["image"]= QString::fromLatin1("Imagem");
        languageMap["pdf"]= QString::fromLatin1("PDF");
        languageMap["export"]= QString::fromLatin1("Exportar");
        languageMap["save_img_success"]= QString::fromLatin1("Arquivo salvo com sucesso!");
        languageMap["save_img_error"]= QString::fromLatin1("Erro ao salvar o aquivo!");
        languageMap["show_graphic"]= QString::fromLatin1("Mostrar gráfico");
        languageMap["table"]= QString::fromLatin1("Matrizes");
        languageMap["criteria"]= QString::fromLatin1("Critério");
        languageMap["alternative"]= QString::fromLatin1("Alternativa");
        languageMap["find"]= QString::fromLatin1("Procurar");
        languageMap["replace"]= QString::fromLatin1("Substituir");
        languageMap["delete_alternative_title"]= QString::fromLatin1("Excluir alternativa");
        languageMap["delete_criteria_title"]= QString::fromLatin1("Excluir critério");

        languageMap["edit_alternative_title"]= QString::fromLatin1("Editar alternativa");
        languageMap["edit_criteria_title"]= QString::fromLatin1("Editar critério");

        languageMap["partial_result"]= QString::fromLatin1("Resultado parcial");
        languageMap["build"]= QString::fromLatin1("Gerar");
        languageMap["next"]= QString::fromLatin1("Próximo");
        languageMap["prev"]= QString::fromLatin1("Anterior");

        languageMap["abscissa_performace_graphic"]= QString::fromLatin1("Critérios combinados");
        languageMap["ordered_performace_graphic"]= QString::fromLatin1("Desempenho");

        languageMap["abicissa_sensibility_graphic"]= QString::fromLatin1("Tau");
        languageMap["sensibility_graphic_percent"]= QString::fromLatin1("Desempenho da melhor alternativa");
        languageMap["sensibility_graphic_quantity"]= QString::fromLatin1("Quantidade de melhores alternativas");
        languageMap["matrix_c"]= QString::fromLatin1("Matriz C");
        languageMap["clean"]= QString::fromLatin1("Limpar");
        languageMap["value"]= QString::fromLatin1("Valor");

        languageMap["open_file"]= QString::fromLatin1("Abrir arquivo");
        languageMap["save_file"]= QString::fromLatin1("Salvar arquivo");
        languageMap["import_table"]= QString::fromLatin1("Importar tabela");
        languageMap["export_table"]= QString::fromLatin1("Exportar tabela");

        languageMap["contact"] = QString::fromLatin1("Contato:");
        languageMap["contact_link"] = QString::fromLatin1("https://github.com/MCDALab/MEM");
        languageMap["license"] = QString::fromLatin1("Licença: GPL ");
        languageMap["version"] = QString::fromLatin1("Versão: 1.0");
    }
    else if( lang == "en" )
    {
        languageMap["open"]="Open";
        languageMap["edit"]="Edit";
        languageMap["new"]="New";
        languageMap["configuration"]="Settings";
        languageMap["title "]="MEM - Multiplex Electionis Methodus";
        languageMap["title_graphic_sensibility"]="Sensibility diagram";
        languageMap["add_criteria_title"]="Add criterion";
        languageMap["add_alternative_title"]="Add alternative";
        languageMap["save"]="Save";
        languageMap["save_as"]="Save as...";
        languageMap["save_new_file_MEM"]="Would you like to save a new MEM file?";
        languageMap["close"]="Close";
        languageMap["english"]="English";
        languageMap["portuguese"]=QString::fromLatin1("Português");
        languageMap["spanish"]= QString::fromLatin1("Español");
        languageMap["franch"]=QString::fromLatin1("François");
        languageMap["matrix_payment"]="Payment matrix";
        languageMap["matrix_weight"]="Weight matrix";
        languageMap["matrix_relationship"]="Complementarity matrix";
        languageMap["files"]="Files";
        languageMap["recent_files"]="Recent files";
        languageMap["language"]="Language";
        languageMap["name_criteria"]="Name criterion";
        languageMap["name_alternative"]="Name alternative";
        languageMap["add"]="Add";
        languageMap["cancel"]="Cancel";
        languageMap["message_null_value_criteria"]="The criterion value cannot be null.";
        languageMap["message_null_value_alternative"]="The alternative value cannot be null.";
        languageMap["message_existing_criteria"]="This criterion name already exists. Please choose a different name.";
        languageMap["message_existing_alternative"]="This alternative name already exists. Please choose a different name.";
        languageMap["mirroring"]="Mirroring";
        languageMap["preference"]="Preference";
        languageMap["preferences"]="Preferences";
        languageMap["growing"]="Increasing";
        languageMap["decreasing"]="Decreasing";
        languageMap["weight"]="Weight";
        languageMap["weights"]="Weights";
        languageMap["about"]="About";
        languageMap["help"]="Help";
        languageMap["matrix_a_line"]="Matrix A'";
        languageMap["matrix_b_line"]="Matrix B'";
        languageMap["apply"]="Apply";
        languageMap["precision"]="Precision";
        languageMap["choices"]="Number of choices";
        languageMap["title_information"]="Information";
        languageMap["table_is_empty"]="Payment table cannot be empty.";
        languageMap["table_is_small"]="Complementarity table is too small.";
        languageMap["table_result_find_info"]="Result: %1 of %2 match(es) found for %3.";
        languageMap["table_result_not_found_info"]="No match found for %1.";
        languageMap["none"]="None";
        languageMap["validate_alternative"]="Alternative %1 still has to be evaluated in regards to criterion %2";
        languageMap["validate_weight"]="A weight still has to be attributed to criterion %1";
        languageMap["validate_criteria"]="The complementarity between criterions %1 and %2 still has to be evaluated.";
        languageMap["matrix_b"]="Matrix B";
        languageMap["result"]="Result";
        languageMap["graphics"]="Diagrams";
        languageMap["menu_sensibility_graphic"]="Sensibility diagram";
        languageMap["menu_graphic_performace"]="Performance of alternative";
        languageMap["image"]="Image";
        languageMap["pdf"]="PDF";
        languageMap["export"]="Export";
        languageMap["save_img_success"]="The file has been successfully saved!";
        languageMap["save_img_error"]="An error has occurred when trying to save the file!";
        languageMap["show_graphic"]="Show diagram";
        languageMap["table"]="Matrices";
        languageMap["criteria"]="Criterion";
        languageMap["alternative"]="Alternative";
        languageMap["find"]="Find";
        languageMap["replace"]="Replace";
        languageMap["delete_alternative_title"]="Delete alternative";
        languageMap["delete_criteria_title"]="Delete criterion";

        languageMap["edit_alternative_title"]="Edit alternative";
        languageMap["edit_criteria_title"]="Edit criterion";

        languageMap["partial_result"]="Partial result";
        languageMap["build"]="Build";
        languageMap["next"]="Next";
        languageMap["prev"]="Previous";

        languageMap["abscissa_performace_graphic"]="Combined criteria";
        languageMap["ordered_performace_graphic"]="Performance";

        languageMap["abicissa_sensibility_graphic"]="Tau";
        languageMap["sensibility_graphic_percent"]="Performance of best alternative";
        languageMap["sensibility_graphic_quantity"]="Quantity of best alternatives";
        languageMap["matrix_c"]="Matrix C";
        languageMap["clean"]="Clear";
        languageMap["value"]="Value";

        languageMap["open_file"]="Open file";
        languageMap["save_file"]="Save file";
        languageMap["import_table"]="Import table";
        languageMap["export_table"]="Export table";

        languageMap["contact"] = QString::fromLatin1("Contact:");
        languageMap["contact_link"] = QString::fromLatin1("https://github.com/MCDALab/MEM");
        languageMap["license"] = QString::fromLatin1("Licese: GPL ");
        languageMap["version"] = QString::fromLatin1("Version: 1.0");
    }
    else if( lang == "es" )
    {
        languageMap["open"] = QString::fromLatin1("Abrir");
        languageMap["edit"] = QString::fromLatin1("Editar");
        languageMap["new"] = QString::fromLatin1("Nuevo");
        languageMap["configuration "] = QString::fromLatin1( "Configuración");
        languageMap["title"] = QString::fromLatin1("MEM-Multiplex Electionis Methodus - Método de Elección Múltiple");
        languageMap["title_graphic_sensibility"] = QString::fromLatin1("Gráfico de sensibilidad");
        languageMap["add_criteria_title"] = QString::fromLatin1("Adicionar criterio");
        languageMap["add_alternative_title"] = QString::fromLatin1("Adicionar alternativa");
        languageMap["save"] = QString::fromLatin1("Guardar");
        languageMap["save_as"] = QString::fromLatin1("Guardar como...");
        languageMap["save_new_file_MEM"] = QString::fromLatin1("Guardar nuevo archivo MEM");
        languageMap["close"] = QString::fromLatin1("Cerrar");
        languageMap["english"] = QString::fromLatin1("English");
        languageMap["portuguese"] = QString::fromLatin1("Português");
        languageMap["spanish"] = QString::fromLatin1("Español");
        languageMap["franch"] = QString::fromLatin1("François");
        languageMap["matrix_payment"] = QString::fromLatin1("Matriz de pagos");
        languageMap["matrix_weight"] = QString::fromLatin1("Matriz de pesos");
        languageMap["matrix_relationship"] = QString::fromLatin1("Matriz de relación");
        languageMap["files"] = QString::fromLatin1("Archivos");
        languageMap["recent_files"] = QString::fromLatin1("Archivos recientes");
        languageMap["language"] = QString::fromLatin1("Idioma");
        languageMap["name_criteria"] = QString::fromLatin1("Nombre del criterio");
        languageMap["name_alternative"] = QString::fromLatin1("Nombre de la alternativa");
        languageMap["add"] = QString::fromLatin1("Adicionar");
        languageMap["cancel"] = QString::fromLatin1("Cancelar");
        languageMap["message_null_value_criteria"] = QString::fromLatin1("El valor del criterio no puede ser nulo");
        languageMap["message_null_value_alternative"] = QString::fromLatin1("El valor de la alternativa no puede ser nulo.");
        languageMap["message_existing_criteria"] = QString::fromLatin1("Este nombre de criterio ya existe, por favor, escoger otro nombre.");
        languageMap["message_existing_alternative"] = QString::fromLatin1("Este nombre de alternativa ya existe, por favor, escoger otro nombre.");
        languageMap["mirroring"] = QString::fromLatin1("Reflejo");
        languageMap["preference"] = QString::fromLatin1("Preferencia");
        languageMap["preferences"] = QString::fromLatin1("Preferencias");
        languageMap["growing"] = QString::fromLatin1("Creciente");
        languageMap["decreasing"] = QString::fromLatin1("Decreciente");
        languageMap["weight"] = QString::fromLatin1("Peso");
        languageMap["weights"] = QString::fromLatin1("Pesos");
        languageMap["about"] = QString::fromLatin1("Acerca de");
        languageMap["help"] = QString::fromLatin1("Ayuda");
        languageMap["matrix_a_line"] = QString::fromLatin1("Matriz A'");
        languageMap["matrix_b_line"] = QString::fromLatin1("Matriz B'");
        languageMap["apply"] = QString::fromLatin1("Aplicar");
        languageMap["precision"] = QString::fromLatin1("Precisión");
        languageMap["choices"] = QString::fromLatin1("Cantidades de selecciones");
        languageMap["title_information"] = QString::fromLatin1("Información");
        languageMap["table_is_empty"] = QString::fromLatin1("La tabla de pagos no puede estar vacía");
        languageMap["table_is_small"] = QString::fromLatin1("La tabla de relaciones es muy pequeña");
        languageMap["table_result_find_info"] = QString::fromLatin1("Resultado: %1 de %2 encontrado(s) para %3.");
        languageMap["table_result_not_found_info"] = QString::fromLatin1("Ningún resultado fue encontrado para %1.");
        languageMap["None"] = QString::fromLatin1("Ninguno");
        languageMap["validate_alternative"] = QString::fromLatin1("Falta evaluar la alternativa %1 en función del Criterio %2");
        languageMap["validate_weight"] = QString::fromLatin1("Falta atribuir peso al criterio %1");
        languageMap["validate_criteria"] = QString::fromLatin1("Falta evaluar la complementariedad entre los criterios %1 e %2");
        languageMap["matrix_b"] = QString::fromLatin1("Matriz B");
        languageMap["result"] = QString::fromLatin1("Resultado");
        languageMap["graphics"] = QString::fromLatin1("Gráficos");
        languageMap["menu_sensibility_graphic"] = QString::fromLatin1("Gráfico de sensibilidad");
        languageMap["menu_graphic_performace"] = QString::fromLatin1("Grafico de desempeño");
        languageMap["image"] = QString::fromLatin1("Imagen");
        languageMap["pdf"] = QString::fromLatin1("PDF");
        languageMap["export"] = QString::fromLatin1("Exportar");
        languageMap["save_img_success"] = QString::fromLatin1("Archivo guardado con éxito!");
        languageMap["save_img_error"] = QString::fromLatin1("Error al guardar el archivo!");
        languageMap["show_graphic"] = QString::fromLatin1("Mostrar gráfico");
        languageMap["table"] = QString::fromLatin1("Matriz");
        languageMap["criteria"] = QString::fromLatin1("Criterio");
        languageMap["alternative"] = QString::fromLatin1("Alternativa");
        languageMap["find"] = QString::fromLatin1("Buscar");
        languageMap["replace"] = QString::fromLatin1("Sustituir");
        languageMap["delete_alternative_title"] = QString::fromLatin1("Excluir alternativa");
        languageMap["delete_criteria_title"] = QString::fromLatin1("Excluir criterio");
        languageMap["edit_alternative_title"] = QString::fromLatin1("Editar alternativa");
        languageMap["edit_criteria_title"] = QString::fromLatin1("Editar criterio");
        languageMap["partial_result"] = QString::fromLatin1("Resultado parcial");
        languageMap["build"] = QString::fromLatin1("Preparar");
        languageMap["next"] = QString::fromLatin1("Próximo");
        languageMap["prev"] = QString::fromLatin1("Anterior");
        languageMap["abscissa_performace_graphic"] = QString::fromLatin1("Criterios combinados");
        languageMap["ordered_performace_graphic"] = QString::fromLatin1("Desempeño");
        languageMap["abicissa_sensibility_graphic"] = QString::fromLatin1("Tau");
        languageMap["sensibility_graphic_percent"] = QString::fromLatin1("Desempeño de la mejor alternativa");
        languageMap["sensibility_graphic_quantity"] = QString::fromLatin1("Cantidad de mejores alternativas");
        languageMap["matrix_c"] = QString::fromLatin1("Matriz C");
        languageMap["clean"] = QString::fromLatin1("Limpiar");
        languageMap["value"] = QString::fromLatin1("Valor");
        languageMap["open_file"] = QString::fromLatin1("Abrir archivo");
        languageMap["save_file"] = QString::fromLatin1("Guardar archivo");
        languageMap["import_table"] = QString::fromLatin1("Importar tabla");
        languageMap["export_table"] = QString::fromLatin1("Exportar tabla");

        languageMap["contact"] = QString::fromLatin1("Contato:");
        languageMap["contact_link"] = QString::fromLatin1("https://github.com/MCDALab/MEM/");
        languageMap["license"] = QString::fromLatin1("Licença: GPL ");
        languageMap["version"] = QString::fromLatin1("Versão: 1.0");
    }
    else if( lang == "fr" )
    {
        languageMap["open"] = QString::fromLatin1("Ouvrir");
        languageMap["edit"] = QString::fromLatin1("Éditer");
        languageMap["new"] = QString::fromLatin1("Nouveau");
        languageMap["configuration"] = QString::fromLatin1("Configuration");
        languageMap["title "] = QString::fromLatin1("MEM - Multiplex Electionis Methodus");
        languageMap["title_graphic_sensibility"] = QString::fromLatin1("Graphique de sensibilité");
        languageMap["add_criteria_title"] = QString::fromLatin1("Ajouter un critère");
        languageMap["add_alternative_title"] = QString::fromLatin1("AAjouter une alternative");
        languageMap["save"] = QString::fromLatin1("Enregistrer");
        languageMap["save_as"] = QString::fromLatin1("Enregistrer sous...");
        languageMap["save_new_file_MEM"] = QString::fromLatin1("Enregistrer um nouvel archive MEM");
        languageMap["close"] = QString::fromLatin1("Fermer");
        languageMap["english"] = QString::fromLatin1("English");
        languageMap["portuguese"] = QString::fromLatin1("Português");
        languageMap["matrix_payment"] = QString::fromLatin1("Matrice de Payement");
        languageMap["matrix_weight"] = QString::fromLatin1("Matrice de poids");
        languageMap["matrix_relationship"] = QString::fromLatin1("Matrice de Complémentarité");
        languageMap["files"] = QString::fromLatin1("Archives");
        languageMap["recent_files"] = QString::fromLatin1("Archives Récents");
        languageMap["language"] = QString::fromLatin1("Langue");
        languageMap["name_criteria"] = QString::fromLatin1("Nom du critère");
        languageMap["name_alternative"] = QString::fromLatin1("Nom de la alternative");
        languageMap["add"] = QString::fromLatin1("Ajouter");
        languageMap["cancel"] = QString::fromLatin1("Annuler");
        languageMap["message_null_value_criteria"] = QString::fromLatin1("La valeur du critère ne peut être nulle");
        languageMap["message_null_value_alternative"] = QString::fromLatin1("La valeur de la Variante ne peut être nulle");
        languageMap["message_existing_criteria"] = QString::fromLatin1("Ce nom de critère éxiste déjà , veuillez choisir un autre nom");
        languageMap["message_existing_alternative"] = QString::fromLatin1("Ce nom de alternative éxiste déjà , veuillez choisir un autre nom");
        languageMap["mirroring"] = QString::fromLatin1("Miroir");
        languageMap["preference"] = QString::fromLatin1("Préference");
        languageMap["preferences"] = QString::fromLatin1("Préferences");
        languageMap["growing"] = QString::fromLatin1("Croissante");
        languageMap["decreasing"] = QString::fromLatin1("Décroissante");
        languageMap["weight"] = QString::fromLatin1("Poids");
        languageMap["weights"] = QString::fromLatin1("Poids");
        languageMap["about"] = QString::fromLatin1("Au sujet de");
        languageMap["help"] = QString::fromLatin1("Aide");
        languageMap["spanish"] = QString::fromLatin1("Español");
        languageMap["franch"] = QString::fromLatin1("Français");
        languageMap["matrix_a_line"] = QString::fromLatin1("Matrice A'");
        languageMap["matrix_b_line"] = QString::fromLatin1("Matrice B'");
        languageMap["apply"] = QString::fromLatin1("Appliquer");
        languageMap["precision"] = QString::fromLatin1("Précison");
        languageMap["choices"] = QString::fromLatin1("Quantité de Choix");
        languageMap["title_information"] = QString::fromLatin1("Information");
        languageMap["table_is_empty"] = QString::fromLatin1("Le tableau de payement ne peut pas être vide");
        languageMap["table_is_small"] = QString::fromLatin1("Le Tableau de Rélations est trop petit");
        languageMap["table_result_find_info"] = QString::fromLatin1("Resultat: 1%, 2% trouvé(s) pour 3%");
        languageMap["table_result_not_found_info"] = QString::fromLatin1("Aucun resultat trouvé pour 1%");
        languageMap["none"] = QString::fromLatin1("Aucun / Aucune");
        languageMap["validate_alternative"] = QString::fromLatin1("Évaluer la variante 1% à la lumière du critère de 2%");
        languageMap["validate_weight"] = QString::fromLatin1("Attribuer un critère au poids 1%");
        languageMap["validate_criteria"] = QString::fromLatin1("Évaluer la complémentarité entre les critères 1% et 2%");
        languageMap["matrix_b"] = QString::fromLatin1("Matrice B");
        languageMap["result"] = QString::fromLatin1("Resultat");
        languageMap["graphics"] = QString::fromLatin1("Graphiques");
        languageMap["menu_sensibility_graphic"] = QString::fromLatin1("Graphique de sensibilité");
        languageMap["menu_graphic_performace"] = QString::fromLatin1("Performance de la alternative");
        languageMap["image"] = QString::fromLatin1("Image");
        languageMap["pdf"] = QString::fromLatin1("PDF");
        languageMap["export"] = QString::fromLatin1("Exporter");
        languageMap["save_img_success"] = QString::fromLatin1("Fichier enregistré avec succès!");
        languageMap["save_img_error"] = QString::fromLatin1("Erreur de fichier!");
        languageMap["show_graphic"] = QString::fromLatin1("Montrer le graphique");
        languageMap["table"] = QString::fromLatin1("Matrice");
        languageMap["criteria"] = QString::fromLatin1("Critère");
        languageMap["alternative"] = QString::fromLatin1("Alternative");
        languageMap["find"] = QString::fromLatin1("Trouver");
        languageMap["replace"] = QString::fromLatin1("Remplacer");
        languageMap["delete_alternative_title"] = QString::fromLatin1("Effacer la alternative");
        languageMap["delete_criteria_title"] = QString::fromLatin1("Effacer le critère");
        languageMap["edit_alternative_title"] = QString::fromLatin1("Modifier la alternative");
        languageMap["edit_criteria_title"] = QString::fromLatin1("Modifier le critère");
        languageMap["partial_result"] = QString::fromLatin1("Resultat Parciel");
        languageMap["build"] = QString::fromLatin1("Construire");
        languageMap["next"] = QString::fromLatin1("Suivant");
        languageMap["prev"] = QString::fromLatin1("Précédent");
        languageMap["abscissa_performace_graphic"] = QString::fromLatin1("Critères combinés");
        languageMap["ordered_performace_graphic"] = QString::fromLatin1("Performance");
        languageMap["abicissa_sensibility_graphic"] = QString::fromLatin1("Tau");
        languageMap["sensibility_graphic_percent"] = QString::fromLatin1("Performance de la meilleure Variante");
        languageMap["sensibility_graphic_quantity"] = QString::fromLatin1("Nombre de meilleures alternatives");
        languageMap["matrix_c"] = QString::fromLatin1("Matrice C");
        languageMap["clean"] = QString::fromLatin1("Nettoyer");
        languageMap["value"] = QString::fromLatin1("Valeur");
        languageMap["open_file"] = QString::fromLatin1("Ouvrir le Fichier");
        languageMap["save_file"] = QString::fromLatin1("Enregistrer le Fichier");
        languageMap["import_table"] = QString::fromLatin1("Importer le tableau");
        languageMap["export_table"] = QString::fromLatin1("Exporter le tableau");

        languageMap["contact"] = QString::fromLatin1("Contato:");
        languageMap["contact_link"] = QString::fromLatin1("https://github.com/MCDALab/MEM/");
        languageMap["license"] = QString::fromLatin1("Licença: GPL ");
        languageMap["version"] = QString::fromLatin1("Versão: 1.0");
    }
}

QString Language::language(QString key)
{
    return languageMap[key];
}

QString Language::actual()
{
    return actual_lang;
}
