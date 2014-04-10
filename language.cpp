#include "language.h"

Language * Language::inst = NULL;
QHash<QString, QString> Language::languageMap;

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
    if( lang == "pt-BR" )
    {
        languageMap["open"] =QString::fromLatin1("Abrir");
        languageMap["edit"] =QString::fromLatin1("Editar");
        languageMap["new"] =QString::fromLatin1("Novo");
        languageMap["configuration"] =QString::fromLatin1("Configura��o");
        languageMap["title"] =QString::fromLatin1("MEM - M�todo de Escolha M�ltipla");
        languageMap["title_graphic_sensibility"] =QString::fromLatin1("Gr�fico de sensibilidade");
        languageMap["add_criteria_title"] =QString::fromLatin1("Adicionar crit�rio");
        languageMap["add_alternative_title"] =QString::fromLatin1("Adicionar alternativa");
        languageMap["save"] =QString::fromLatin1("Salvar");
        languageMap["save_as"] =QString::fromLatin1("Salvar como ...");
        languageMap["save_new_file_MEM"] =QString::fromLatin1("Deseja salvar um novo arquivo MEM");
        languageMap["close"] =QString::fromLatin1("Fechar");
        languageMap["english"] =QString::fromLatin1("Ingl�s");
        languageMap["portuguese"] =QString::fromLatin1("Portugu�s");
        languageMap["matrix_payment"] =QString::fromLatin1("Matriz pagamento");
        languageMap["matrix_weight"] =QString::fromLatin1("Matriz pesos");
        languageMap["matrix_relationship"] =QString::fromLatin1("Matriz complementariedade");
        languageMap["files"] =QString::fromLatin1("Arquivos");
        languageMap["recent_files"] =QString::fromLatin1("Arquivos recentes");
        languageMap["language"] =QString::fromLatin1("Linguagem");
        languageMap["name_criteria"] =QString::fromLatin1("Nome crit�rio");
        languageMap["name_alternative"] =QString::fromLatin1("Nome alternativa");
        languageMap["add"] =QString::fromLatin1("Adicionar");
        languageMap["cancel"] =QString::fromLatin1("Cancelar");
        languageMap["message_null_value_criteria"] =QString::fromLatin1("O valor do crit�rio n�o pode ser nulo.");
        languageMap["message_null_value_alternative"] =QString::fromLatin1("O valor da alternativa n�o pode ser nulo.");
        languageMap["message_existing_criteria"] =QString::fromLatin1("O crit�rio j� existe, escolha outro nome.");
        languageMap["message_existing_alternative"] =QString::fromLatin1("A alternativa j� existe, escolha outro nome.");
        languageMap["mirroring"] =QString::fromLatin1("Espelhamento");
        languageMap["preference"] =QString::fromLatin1("Prefer�ncia");
        languageMap["preferences"] =QString::fromLatin1("Prefer�ncias");
        languageMap["growing"] =QString::fromLatin1("Crescente");
        languageMap["decreasing"] =QString::fromLatin1("Decrescente");
        languageMap["weight"] =QString::fromLatin1("Peso");
        languageMap["weights"] =QString::fromLatin1("Pesos");
        languageMap["about"] =QString::fromLatin1("Sobre");
        languageMap["help"] =QString::fromLatin1("Ajuda");
        languageMap["spanish"] =QString::fromLatin1("Espanhol");
        languageMap["franch"] =QString::fromLatin1("Franc�s");
        languageMap["matrix_a_line"] =QString::fromLatin1("Matriz A'");
        languageMap["matrix_b_line"] =QString::fromLatin1("Matrix B'");
        languageMap["apply"] =QString::fromLatin1("Aplicar");
        languageMap["precision"] =QString::fromUtf8( "Precis�o");
        languageMap["choices"] =QString::fromLatin1("Quantidade de escolhas");
        languageMap["title_information"] =QString::fromLatin1("Informa��o");
        languageMap["table_is_empty"] =QString::fromLatin1("Tabela de pagamento n�o pode esta v�zia.");
        languageMap["table_is_small"] =QString::fromLatin1("Tabela de relacionamento pequena de mais.");
        languageMap["table_result_find_info"] =QString::fromLatin1("Resultado: %1 de %2 encontrado(s) para %3.");
        languageMap["table_result_not_found_info"] =QString::fromLatin1("Nenhum resultado encontrado para %1.");
        languageMap["none"] =QString::fromLatin1("Nenhum");
        languageMap["validate_alternative"] =QString::fromLatin1("Falta avaliar a alternativa %1 � luz do Crit�rio %2");
        languageMap["validate_weight"] =QString::fromLatin1("Falta atribuir um peso ao crit�rio %1");
        languageMap["validate_criteria"] =QString::fromLatin1("Falta avaliar a complementariedade entre os crit�rios %1 e %2.");
        languageMap["matrix_b"] =QString::fromLatin1("Matriz B");
        languageMap["result"] =QString::fromLatin1("Resultado");
        languageMap["graphics"] =QString::fromLatin1("Gr�ficos");
        languageMap["menu_sensibility_graphic"] =QString::fromLatin1("Gr�fico de Sensibilidade");
        languageMap["menu_graphic_performace"] =QString::fromLatin1("Desempenho de alternativa");
        languageMap["image"] =QString::fromLatin1("Imagem");
        languageMap["pdf"] =QString::fromLatin1("PDF");
        languageMap["export"] =QString::fromLatin1("Exportar");
        languageMap["save_img_success"] =QString::fromLatin1("Arquivo salvo com sucesso!");
        languageMap["save_img_error"] =QString::fromLatin1("Erro ao salvar aquivo!");
        languageMap["show_graphic"] =QString::fromLatin1("Mostrar gr�fico");
        languageMap["table"] =QString::fromLatin1("Matrizes");
        languageMap["criteria"] =QString::fromLatin1("Crit�rio");
        languageMap["alternative"] =QString::fromLatin1("Alternativa");
        languageMap["find"] =QString::fromLatin1("Procurar");
        languageMap["replace"] =QString::fromLatin1("Substituir");
        languageMap["delete_alternative_title"] =QString::fromLatin1("Excluir alternativa");
        languageMap["delete_criteria_title"] =QString::fromLatin1("Excluir crit�rio");

        languageMap["edit_alternative_title"] =QString::fromLatin1("Editar alternativa");
        languageMap["edit_criteria_title"] =QString::fromLatin1("Editar crit�rio");

        languageMap["partial_result"] =QString::fromLatin1("Resultado parcial");
        languageMap["build"] =QString::fromLatin1("Gerar");
        languageMap["next"] =QString::fromLatin1("Pr�ximo");
        languageMap["prev"] =QString::fromLatin1("Anterior");

        languageMap["abscissa_performace_graphic"] =QString::fromLatin1("Abiscissa gr�fico de desempenho de alternativa");
        languageMap["ordered_performace_graphic"] =QString::fromLatin1("Ordenada gr�fico de desempenho de alternativa");

        languageMap["abicissa_sensibility_graphic"] =QString::fromUtf8( "Abiscissa gr�fico de desempenho de sensibilidade");
        languageMap["sensibility_graphic_percent"] =QString::fromLatin1("Ordenada gr�fico de desempenho de sensibilidade porcentagem");
        languageMap["sensibility_graphic_quantity"] =QString::fromLatin1("ordenada de Quantidade");
        languageMap["matrix_c"] =QString::fromLatin1("Matriz C");
        languageMap["clean"] =QString::fromLatin1("Limpar");
        languageMap["title_col"] = QString::fromLatin1("T�tulo");
        languageMap["value"] =QString::fromLatin1("Valor");

        languageMap["open_file"] =QString::fromLatin1("Abrir arquivo");
        languageMap["save_file"] =QString::fromLatin1("Salvar arquivo");
        languageMap["import_table"] =QString::fromLatin1("Importar tabela");
        languageMap["export_table"] =QString::fromLatin1("Exportar tabela");
    }
    else if( lang == "en" )
    {
        languageMap["open"] =QString::fromLatin1("Abrir");
        languageMap["edit"] =QString::fromLatin1("Editar");
        languageMap["new"] =QString::fromLatin1("Novo");
        languageMap["configuration"] =QString::fromLatin1("Configura��o");
        languageMap["title"] =QString::fromLatin1("MEM - M�todo de Escolha M�ltipla");
        languageMap["title_graphic_sensibility"] =QString::fromLatin1("Gr�fico de sensibilidade");
        languageMap["add_criteria_title"] =QString::fromLatin1("Adicionar crit�rio");
        languageMap["add_alternative_title"] =QString::fromLatin1("Adicionar alternativa");
        languageMap["save"] =QString::fromLatin1("Salvar");
        languageMap["save_as"] =QString::fromLatin1("Salvar como ...");
        languageMap["save_new_file_MEM"] =QString::fromLatin1("Deseja salvar um novo arquivo MEM");
        languageMap["close"] =QString::fromLatin1("Fechar");
        languageMap["english"] =QString::fromLatin1("Ingl�s");
        languageMap["portuguese"] =QString::fromLatin1("Portugu�s");
        languageMap["matrix_payment"] =QString::fromLatin1("Matriz pagamento");
        languageMap["matrix_weight"] =QString::fromLatin1("Matriz pesos");
        languageMap["matrix_relationship"] =QString::fromLatin1("Matriz complementariedade");
        languageMap["files"] =QString::fromLatin1("Arquivos");
        languageMap["recent_files"] =QString::fromLatin1("Arquivos recentes");
        languageMap["language"] =QString::fromLatin1("Linguagem");
        languageMap["name_criteria"] =QString::fromLatin1("Nome crit�rio");
        languageMap["name_alternative"] =QString::fromLatin1("Nome alternativa");
        languageMap["add"] =QString::fromLatin1("Adicionar");
        languageMap["cancel"] =QString::fromLatin1("Cancelar");
        languageMap["message_null_value_criteria"] =QString::fromLatin1("O valor do crit�rio n�o pode ser nulo.");
        languageMap["message_null_value_alternative"] =QString::fromLatin1("O valor da alternativa n�o pode ser nulo.");
        languageMap["message_existing_criteria"] =QString::fromLatin1("O crit�rio j� existe, escolha outro nome.");
        languageMap["message_existing_alternative"] =QString::fromLatin1("A alternativa j� existe, escolha outro nome.");
        languageMap["mirroring"] =QString::fromLatin1("Espelhamento");
        languageMap["preference"] =QString::fromLatin1("Prefer�ncia");
        languageMap["preferences"] =QString::fromLatin1("Prefer�ncias");
        languageMap["growing"] =QString::fromLatin1("Crescente");
        languageMap["decreasing"] =QString::fromLatin1("Decrescente");
        languageMap["weight"] =QString::fromLatin1("Peso");
        languageMap["weights"] =QString::fromLatin1("Pesos");
        languageMap["about"] =QString::fromLatin1("Sobre");
        languageMap["help"] =QString::fromLatin1("Ajuda");
        languageMap["spanish"] =QString::fromLatin1("Espanhol");
        languageMap["franch"] =QString::fromLatin1("Franc�s");
        languageMap["matrix_a_line"] =QString::fromLatin1("Matriz A'");
        languageMap["matrix_b_line"] =QString::fromLatin1("Matrix B'");
        languageMap["apply"] =QString::fromLatin1("Aplicar");
        languageMap["precision"] =QString::fromUtf8( "Precis�o");
        languageMap["choices"] =QString::fromLatin1("Quantidade de escolhas");
        languageMap["title_information"] =QString::fromLatin1("Informa��o");
        languageMap["table_is_empty"] =QString::fromLatin1("Tabela de pagamento n�o pode esta v�zia.");
        languageMap["table_is_small"] =QString::fromLatin1("Tabela de relacionamento pequena de mais.");
        languageMap["table_result_find_info"] =QString::fromLatin1("Resultado: %1 de %2 encontrado(s) para %3.");
        languageMap["table_result_not_found_info"] =QString::fromLatin1("Nenhum resultado encontrado para %1.");
        languageMap["none"] =QString::fromLatin1("Nenhum");
        languageMap["validate_alternative"] =QString::fromLatin1("Falta avaliar a alternativa %1 � luz do Crit�rio %2");
        languageMap["validate_weight"] =QString::fromLatin1("Falta atribuir um peso ao crit�rio %1");
        languageMap["validate_criteria"] =QString::fromLatin1("Falta avaliar a complementariedade entre os crit�rios %1 e %2.");
        languageMap["matrix_b"] =QString::fromLatin1("Matriz B");
        languageMap["result"] =QString::fromLatin1("Resultado");
        languageMap["graphics"] =QString::fromLatin1("Gr�ficos");
        languageMap["menu_sensibility_graphic"] =QString::fromLatin1("Gr�fico de Sensibilidade");
        languageMap["menu_graphic_performace"] =QString::fromLatin1("Desempenho de alternativa");
        languageMap["image"] =QString::fromLatin1("Imagem");
        languageMap["pdf"] =QString::fromLatin1("PDF");
        languageMap["export"] =QString::fromLatin1("Exportar");
        languageMap["save_img_success"] =QString::fromLatin1("Arquivo salvo com sucesso!");
        languageMap["save_img_error"] =QString::fromLatin1("Erro ao salvar aquivo!");
        languageMap["show_graphic"] =QString::fromLatin1("Mostrar gr�fico");
        languageMap["table"] =QString::fromLatin1("Matrizes");
        languageMap["criteria"] =QString::fromLatin1("Crit�rio");
        languageMap["alternative"] =QString::fromLatin1("Alternativa");
        languageMap["find"] =QString::fromLatin1("Procurar");
        languageMap["replace"] =QString::fromLatin1("Substituir");
        languageMap["delete_alternative_title"] =QString::fromLatin1("Excluir alternativa");
        languageMap["delete_criteria_title"] =QString::fromLatin1("Excluir crit�rio");

        languageMap["edit_alternative_title"] =QString::fromLatin1("Editar alternativa");
        languageMap["edit_criteria_title"] =QString::fromLatin1("Editar crit�rio");

        languageMap["partial_result"] =QString::fromLatin1("Resultado parcial");
        languageMap["build"] =QString::fromLatin1("Gerar");
        languageMap["next"] =QString::fromLatin1("Pr�ximo");
        languageMap["prev"] =QString::fromLatin1("Anterior");

        languageMap["abscissa_performace_graphic"] =QString::fromLatin1("Abiscissa gr�fico de desempenho de alternativa");
        languageMap["ordered_performace_graphic"] =QString::fromLatin1("Ordenada gr�fico de desempenho de alternativa");

        languageMap["abicissa_sensibility_graphic"] =QString::fromUtf8( "Abiscissa gr�fico de desempenho de sensibilidade");
        languageMap["sensibility_graphic_percent"] =QString::fromLatin1("Ordenada gr�fico de desempenho de sensibilidade porcentagem");
        languageMap["sensibility_graphic_quantity"] =QString::fromLatin1("ordenada de Quantidade");
        languageMap["matrix_c"] =QString::fromLatin1("Matriz C");
        languageMap["clean"] =QString::fromLatin1("Limpar");
        languageMap["title_col"] = QString::fromLatin1("T�tulo");
        languageMap["value"] =QString::fromLatin1("Valor");

        languageMap["open_file"] =QString::fromLatin1("Abrir arquivo");
        languageMap["save_file"] =QString::fromLatin1("Salvar arquivo");
        languageMap["import_table"] =QString::fromLatin1("Importar tabela");
        languageMap["export_table"] =QString::fromLatin1("Exportar tabela");
    }
    else if( lang == "es" )
    {
        languageMap["open"] =QString::fromLatin1("Abrir");
        languageMap["edit"] =QString::fromLatin1("Editar");
        languageMap["new"] =QString::fromLatin1("Novo");
        languageMap["configuration"] =QString::fromLatin1("Configura��o");
        languageMap["title"] =QString::fromLatin1("MEM - M�todo de Escolha M�ltipla");
        languageMap["title_graphic_sensibility"] =QString::fromLatin1("Gr�fico de sensibilidade");
        languageMap["add_criteria_title"] =QString::fromLatin1("Adicionar crit�rio");
        languageMap["add_alternative_title"] =QString::fromLatin1("Adicionar alternativa");
        languageMap["save"] =QString::fromLatin1("Salvar");
        languageMap["save_as"] =QString::fromLatin1("Salvar como ...");
        languageMap["save_new_file_MEM"] =QString::fromLatin1("Deseja salvar um novo arquivo MEM");
        languageMap["close"] =QString::fromLatin1("Fechar");
        languageMap["english"] =QString::fromLatin1("Ingl�s");
        languageMap["portuguese"] =QString::fromLatin1("Portugu�s");
        languageMap["matrix_payment"] =QString::fromLatin1("Matriz pagamento");
        languageMap["matrix_weight"] =QString::fromLatin1("Matriz pesos");
        languageMap["matrix_relationship"] =QString::fromLatin1("Matriz complementariedade");
        languageMap["files"] =QString::fromLatin1("Arquivos");
        languageMap["recent_files"] =QString::fromLatin1("Arquivos recentes");
        languageMap["language"] =QString::fromLatin1("Linguagem");
        languageMap["name_criteria"] =QString::fromLatin1("Nome crit�rio");
        languageMap["name_alternative"] =QString::fromLatin1("Nome alternativa");
        languageMap["add"] =QString::fromLatin1("Adicionar");
        languageMap["cancel"] =QString::fromLatin1("Cancelar");
        languageMap["message_null_value_criteria"] =QString::fromLatin1("O valor do crit�rio n�o pode ser nulo.");
        languageMap["message_null_value_alternative"] =QString::fromLatin1("O valor da alternativa n�o pode ser nulo.");
        languageMap["message_existing_criteria"] =QString::fromLatin1("O crit�rio j� existe, escolha outro nome.");
        languageMap["message_existing_alternative"] =QString::fromLatin1("A alternativa j� existe, escolha outro nome.");
        languageMap["mirroring"] =QString::fromLatin1("Espelhamento");
        languageMap["preference"] =QString::fromLatin1("Prefer�ncia");
        languageMap["preferences"] =QString::fromLatin1("Prefer�ncias");
        languageMap["growing"] =QString::fromLatin1("Crescente");
        languageMap["decreasing"] =QString::fromLatin1("Decrescente");
        languageMap["weight"] =QString::fromLatin1("Peso");
        languageMap["weights"] =QString::fromLatin1("Pesos");
        languageMap["about"] =QString::fromLatin1("Sobre");
        languageMap["help"] =QString::fromLatin1("Ajuda");
        languageMap["spanish"] =QString::fromLatin1("Espanhol");
        languageMap["franch"] =QString::fromLatin1("Franc�s");
        languageMap["matrix_a_line"] =QString::fromLatin1("Matriz A'");
        languageMap["matrix_b_line"] =QString::fromLatin1("Matrix B'");
        languageMap["apply"] =QString::fromLatin1("Aplicar");
        languageMap["precision"] =QString::fromUtf8( "Precis�o");
        languageMap["choices"] =QString::fromLatin1("Quantidade de escolhas");
        languageMap["title_information"] =QString::fromLatin1("Informa��o");
        languageMap["table_is_empty"] =QString::fromLatin1("Tabela de pagamento n�o pode esta v�zia.");
        languageMap["table_is_small"] =QString::fromLatin1("Tabela de relacionamento pequena de mais.");
        languageMap["table_result_find_info"] =QString::fromLatin1("Resultado: %1 de %2 encontrado(s) para %3.");
        languageMap["table_result_not_found_info"] =QString::fromLatin1("Nenhum resultado encontrado para %1.");
        languageMap["none"] =QString::fromLatin1("Nenhum");
        languageMap["validate_alternative"] =QString::fromLatin1("Falta avaliar a alternativa %1 � luz do Crit�rio %2");
        languageMap["validate_weight"] =QString::fromLatin1("Falta atribuir um peso ao crit�rio %1");
        languageMap["validate_criteria"] =QString::fromLatin1("Falta avaliar a complementariedade entre os crit�rios %1 e %2.");
        languageMap["matrix_b"] =QString::fromLatin1("Matriz B");
        languageMap["result"] =QString::fromLatin1("Resultado");
        languageMap["graphics"] =QString::fromLatin1("Gr�ficos");
        languageMap["menu_sensibility_graphic"] =QString::fromLatin1("Gr�fico de Sensibilidade");
        languageMap["menu_graphic_performace"] =QString::fromLatin1("Desempenho de alternativa");
        languageMap["image"] =QString::fromLatin1("Imagem");
        languageMap["pdf"] =QString::fromLatin1("PDF");
        languageMap["export"] =QString::fromLatin1("Exportar");
        languageMap["save_img_success"] =QString::fromLatin1("Arquivo salvo com sucesso!");
        languageMap["save_img_error"] =QString::fromLatin1("Erro ao salvar aquivo!");
        languageMap["show_graphic"] =QString::fromLatin1("Mostrar gr�fico");
        languageMap["table"] =QString::fromLatin1("Matrizes");
        languageMap["criteria"] =QString::fromLatin1("Crit�rio");
        languageMap["alternative"] =QString::fromLatin1("Alternativa");
        languageMap["find"] =QString::fromLatin1("Procurar");
        languageMap["replace"] =QString::fromLatin1("Substituir");
        languageMap["delete_alternative_title"] =QString::fromLatin1("Excluir alternativa");
        languageMap["delete_criteria_title"] =QString::fromLatin1("Excluir crit�rio");

        languageMap["edit_alternative_title"] =QString::fromLatin1("Editar alternativa");
        languageMap["edit_criteria_title"] =QString::fromLatin1("Editar crit�rio");

        languageMap["partial_result"] =QString::fromLatin1("Resultado parcial");
        languageMap["build"] =QString::fromLatin1("Gerar");
        languageMap["next"] =QString::fromLatin1("Pr�ximo");
        languageMap["prev"] =QString::fromLatin1("Anterior");

        languageMap["abscissa_performace_graphic"] =QString::fromLatin1("Abiscissa gr�fico de desempenho de alternativa");
        languageMap["ordered_performace_graphic"] =QString::fromLatin1("Ordenada gr�fico de desempenho de alternativa");

        languageMap["abicissa_sensibility_graphic"] =QString::fromUtf8( "Abiscissa gr�fico de desempenho de sensibilidade");
        languageMap["sensibility_graphic_percent"] =QString::fromLatin1("Ordenada gr�fico de desempenho de sensibilidade porcentagem");
        languageMap["sensibility_graphic_quantity"] =QString::fromLatin1("ordenada de Quantidade");
        languageMap["matrix_c"] =QString::fromLatin1("Matriz C");
        languageMap["clean"] =QString::fromLatin1("Limpar");
        languageMap["title_col"] = QString::fromLatin1("T�tulo");
        languageMap["value"] =QString::fromLatin1("Valor");

        languageMap["open_file"] =QString::fromLatin1("Abrir arquivo");
        languageMap["save_file"] =QString::fromLatin1("Salvar arquivo");
        languageMap["import_table"] =QString::fromLatin1("Importar tabela");
        languageMap["export_table"] =QString::fromLatin1("Exportar tabela");
    }
    else if( lang == "fr" )
    {
        languageMap["open"] =QString::fromLatin1("Abrir");
        languageMap["edit"] =QString::fromLatin1("Editar");
        languageMap["new"] =QString::fromLatin1("Novo");
        languageMap["configuration"] =QString::fromLatin1("Configura��o");
        languageMap["title"] =QString::fromLatin1("MEM - M�todo de Escolha M�ltipla");
        languageMap["title_graphic_sensibility"] =QString::fromLatin1("Gr�fico de sensibilidade");
        languageMap["add_criteria_title"] =QString::fromLatin1("Adicionar crit�rio");
        languageMap["add_alternative_title"] =QString::fromLatin1("Adicionar alternativa");
        languageMap["save"] =QString::fromLatin1("Salvar");
        languageMap["save_as"] =QString::fromLatin1("Salvar como ...");
        languageMap["save_new_file_MEM"] =QString::fromLatin1("Deseja salvar um novo arquivo MEM");
        languageMap["close"] =QString::fromLatin1("Fechar");
        languageMap["english"] =QString::fromLatin1("Ingl�s");
        languageMap["portuguese"] =QString::fromLatin1("Portugu�s");
        languageMap["matrix_payment"] =QString::fromLatin1("Matriz pagamento");
        languageMap["matrix_weight"] =QString::fromLatin1("Matriz pesos");
        languageMap["matrix_relationship"] =QString::fromLatin1("Matriz complementariedade");
        languageMap["files"] =QString::fromLatin1("Arquivos");
        languageMap["recent_files"] =QString::fromLatin1("Arquivos recentes");
        languageMap["language"] =QString::fromLatin1("Linguagem");
        languageMap["name_criteria"] =QString::fromLatin1("Nome crit�rio");
        languageMap["name_alternative"] =QString::fromLatin1("Nome alternativa");
        languageMap["add"] =QString::fromLatin1("Adicionar");
        languageMap["cancel"] =QString::fromLatin1("Cancelar");
        languageMap["message_null_value_criteria"] =QString::fromLatin1("O valor do crit�rio n�o pode ser nulo.");
        languageMap["message_null_value_alternative"] =QString::fromLatin1("O valor da alternativa n�o pode ser nulo.");
        languageMap["message_existing_criteria"] =QString::fromLatin1("O crit�rio j� existe, escolha outro nome.");
        languageMap["message_existing_alternative"] =QString::fromLatin1("A alternativa j� existe, escolha outro nome.");
        languageMap["mirroring"] =QString::fromLatin1("Espelhamento");
        languageMap["preference"] =QString::fromLatin1("Prefer�ncia");
        languageMap["preferences"] =QString::fromLatin1("Prefer�ncias");
        languageMap["growing"] =QString::fromLatin1("Crescente");
        languageMap["decreasing"] =QString::fromLatin1("Decrescente");
        languageMap["weight"] =QString::fromLatin1("Peso");
        languageMap["weights"] =QString::fromLatin1("Pesos");
        languageMap["about"] =QString::fromLatin1("Sobre");
        languageMap["help"] =QString::fromLatin1("Ajuda");
        languageMap["spanish"] =QString::fromLatin1("Espanhol");
        languageMap["franch"] =QString::fromLatin1("Franc�s");
        languageMap["matrix_a_line"] =QString::fromLatin1("Matriz A'");
        languageMap["matrix_b_line"] =QString::fromLatin1("Matrix B'");
        languageMap["apply"] =QString::fromLatin1("Aplicar");
        languageMap["precision"] =QString::fromUtf8( "Precis�o");
        languageMap["choices"] =QString::fromLatin1("Quantidade de escolhas");
        languageMap["title_information"] =QString::fromLatin1("Informa��o");
        languageMap["table_is_empty"] =QString::fromLatin1("Tabela de pagamento n�o pode esta v�zia.");
        languageMap["table_is_small"] =QString::fromLatin1("Tabela de relacionamento pequena de mais.");
        languageMap["table_result_find_info"] =QString::fromLatin1("Resultado: %1 de %2 encontrado(s) para %3.");
        languageMap["table_result_not_found_info"] =QString::fromLatin1("Nenhum resultado encontrado para %1.");
        languageMap["none"] =QString::fromLatin1("Nenhum");
        languageMap["validate_alternative"] =QString::fromLatin1("Falta avaliar a alternativa %1 � luz do Crit�rio %2");
        languageMap["validate_weight"] =QString::fromLatin1("Falta atribuir um peso ao crit�rio %1");
        languageMap["validate_criteria"] =QString::fromLatin1("Falta avaliar a complementariedade entre os crit�rios %1 e %2.");
        languageMap["matrix_b"] =QString::fromLatin1("Matriz B");
        languageMap["result"] =QString::fromLatin1("Resultado");
        languageMap["graphics"] =QString::fromLatin1("Gr�ficos");
        languageMap["menu_sensibility_graphic"] =QString::fromLatin1("Gr�fico de Sensibilidade");
        languageMap["menu_graphic_performace"] =QString::fromLatin1("Desempenho de alternativa");
        languageMap["image"] =QString::fromLatin1("Imagem");
        languageMap["pdf"] =QString::fromLatin1("PDF");
        languageMap["export"] =QString::fromLatin1("Exportar");
        languageMap["save_img_success"] =QString::fromLatin1("Arquivo salvo com sucesso!");
        languageMap["save_img_error"] =QString::fromLatin1("Erro ao salvar aquivo!");
        languageMap["show_graphic"] =QString::fromLatin1("Mostrar gr�fico");
        languageMap["table"] =QString::fromLatin1("Matrizes");
        languageMap["criteria"] =QString::fromLatin1("Crit�rio");
        languageMap["alternative"] =QString::fromLatin1("Alternativa");
        languageMap["find"] =QString::fromLatin1("Procurar");
        languageMap["replace"] =QString::fromLatin1("Substituir");
        languageMap["delete_alternative_title"] =QString::fromLatin1("Excluir alternativa");
        languageMap["delete_criteria_title"] =QString::fromLatin1("Excluir crit�rio");

        languageMap["edit_alternative_title"] =QString::fromLatin1("Editar alternativa");
        languageMap["edit_criteria_title"] =QString::fromLatin1("Editar crit�rio");

        languageMap["partial_result"] =QString::fromLatin1("Resultado parcial");
        languageMap["build"] =QString::fromLatin1("Gerar");
        languageMap["next"] =QString::fromLatin1("Pr�ximo");
        languageMap["prev"] =QString::fromLatin1("Anterior");

        languageMap["abscissa_performace_graphic"] =QString::fromLatin1("Abiscissa gr�fico de desempenho de alternativa");
        languageMap["ordered_performace_graphic"] =QString::fromLatin1("Ordenada gr�fico de desempenho de alternativa");

        languageMap["abicissa_sensibility_graphic"] =QString::fromUtf8( "Abiscissa gr�fico de desempenho de sensibilidade");
        languageMap["sensibility_graphic_percent"] =QString::fromLatin1("Ordenada gr�fico de desempenho de sensibilidade porcentagem");
        languageMap["sensibility_graphic_quantity"] =QString::fromLatin1("ordenada de Quantidade");
        languageMap["matrix_c"] =QString::fromLatin1("Matriz C");
        languageMap["clean"] =QString::fromLatin1("Limpar");
        languageMap["title_col"] = QString::fromLatin1("T�tulo");
        languageMap["value"] =QString::fromLatin1("Valor");

        languageMap["open_file"] =QString::fromLatin1("Abrir arquivo");
        languageMap["save_file"] =QString::fromLatin1("Salvar arquivo");
        languageMap["import_table"] =QString::fromLatin1("Importar tabela");
        languageMap["export_table"] =QString::fromLatin1("Exportar tabela");
    }
}

QString Language::language(QString key)
{
    return languageMap[key];
}
