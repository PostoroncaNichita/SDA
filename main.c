#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER 1000

typedef struct Product {
    struct tm sale_date;
    int product_id;
    char product_name[MAX_BUFFER];
    char product_category[MAX_BUFFER];
    char product_subcategory[MAX_BUFFER];
    float unit_price;
    int quantity_sold;
    char sale_country[MAX_BUFFER];
    char sale_city[MAX_BUFFER];
} Product;

typedef struct Category {
    char category_name[MAX_BUFFER];
    float montly_sales[12];
} Category;

int compare_by_product_value(const void *a, const void *b);

void _insert_product_details_(Product *products, char *line, int index);

void read_file(Product **products, int *number_of_products, FILE *file);

void top_5_products_by_value(Product *products);

void print_monthly_profit(Product *products, int number_of_products);

void sales_category_creation(Product *products, int number_of_products);

void _print_sales_category_(Category *categories, int number_of_categories);

int main() {
    FILE *file = fopen("sales.csv", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int number_of_products = 0;
    Product *products = NULL;

    read_file(&products, &number_of_products, file);

    printf("Done inserting\n");

    qsort(products, number_of_products, sizeof(Product), compare_by_product_value);

    top_5_products_by_value(products);

    print_monthly_profit(products, number_of_products);

    sales_category_creation(products, number_of_products);

    printf("Data written to files");

    fclose(file);
    free(products);
    return 0;
}

void _insert_product_details_(Product *products, char *line, int index) {
    const char delimiter[] = ",";
    char *token = strtok(line, ",");

    sscanf(token, "%d-%d-%d", &products[index].sale_date.tm_year, &products[index].sale_date.tm_mon, &products[index].sale_date.tm_mday);
    token = strtok(NULL, delimiter);
    products[index].sale_date.tm_mon--;

    products[index].product_id = atoi(token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].product_name, token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].product_category, token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].product_subcategory, token);
    token = strtok(NULL, delimiter);

    products[index].unit_price = atof(token);
    token = strtok(NULL, delimiter);

    products[index].quantity_sold = atoi(token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].sale_country, token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].sale_city, token);
    products[index].sale_city[strcspn(products[index].sale_city, "\n")] = '\0';
}

void read_file(Product **products, int *number_of_products, FILE *file) {
    char line[MAX_BUFFER];

    int realloc_value = 1;

    // Skip header line
    if (fgets(line, MAX_BUFFER, file) == NULL) {
        printf("Error reading file\n");
        exit(1);
    }

    while (fgets(line, MAX_BUFFER, file) != NULL) {
        // Allocate memory for the new product

        if (realloc_value == *number_of_products) {
            realloc_value *= 2;
        }

        *products = realloc(*products, sizeof(Product) * (realloc_value));
        if (*products == NULL) {
            printf("Error reallocating memory\n");
            exit(1);
        }

        // Insert product details into the array
        _insert_product_details_(*products, line, *number_of_products);
        (*number_of_products)++;
    }

    *products = realloc(*products, sizeof(Product) * (*number_of_products));
}

int compare_by_product_value(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;

    float totalA = productA->unit_price * productA->quantity_sold;
    float totalB = productB->unit_price * productB->quantity_sold;

    if (totalA > totalB) return -1;
    else if (totalA < totalB) return 1;
    else return 0;
}

void top_5_products_by_value(Product *products) {

    FILE *top_products = fopen("top_products.txt", "w");

    for (int i = 0; i < 5; ++i) {
        fprintf(top_products, "Sale_date: %d-%02d-%02d\t Product_id_%d: %d\n", products[i].sale_date.tm_year, products[i].sale_date.tm_mon, products[i].sale_date.tm_mday, i + 1, products[i].product_id);
    }

    fclose(top_products);
}

void print_monthly_profit(Product *products, int number_of_products) {
    float years_profit[55][13] = {0};
    float year = 1970;

    for (int i = 0; i < 55; ++i) {
        years_profit[i][0] = year;
        year++;
    }

    for (int i = 0; i < number_of_products; i++) {
        float product_value = products[i].unit_price * products[i].quantity_sold;
        int year_index = products[i].sale_date.tm_year - 1970;
        int month_index = products[i].sale_date.tm_mon + 1;
        years_profit[year_index][month_index] += product_value;
    }

    FILE *yearly_profit = fopen("yearly_profit.txt", "w");

    fprintf(yearly_profit, "%s%12s%16s%16s%16s%16s%16s%16s%16s%16s%16s%16s%16s", "Year", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");
    fprintf(yearly_profit, "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 55; ++i) {
        fprintf(yearly_profit,"%.0f\t", years_profit[i][0]);
        for (int j = 1; j < 13; ++j) {
            fprintf(yearly_profit, "%15.2f\t", years_profit[i][j]);
        }

        fprintf(yearly_profit, "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(yearly_profit);
}

void _print_sales_category_(Category *categories, int number_of_categories) {

    FILE *category_profit = fopen("category_profit.txt", "w");

    fprintf(category_profit, "%s%12s%16s%16s%16s%16s%16s%16s%16s%16s%16s%16s%16s", "Category", "Jan", "Feb", "Mar", "Apr","May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");

    fprintf(category_profit,"\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < number_of_categories; ++i) {

        fprintf(category_profit, "%s\t", categories[i].category_name);
        for (int j = 0; j < 12; ++j) {
            fprintf(category_profit, "%14.2f", categories[i].montly_sales[j]);
        }

        fprintf(category_profit, "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    }
    fclose(category_profit);
}

void sales_category_creation(Product *products, int number_of_products) {
    Category *categories = NULL;
    int number_of_categories = 0;

    categories = (struct Category *)malloc(sizeof(Category));
    if (categories == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    for (int i = 0; i < number_of_products; i++) {
        int category_found = 0;

        for (int j = 0; j < number_of_categories; ++j) {
            if (strcmp(products[i].product_category, categories[j].category_name) == 0) {
                categories[j].montly_sales[products[i].sale_date.tm_mon] += products[i].unit_price * products[i].quantity_sold;
                category_found = 1;
                break;
            }
        }

        if (!category_found) {
            categories = (struct Category *)realloc(categories, sizeof(Category) * (number_of_categories + 2));
            if (categories == NULL) {
                printf("Error reallocating memory for new category\n");
                exit(1);
            }

            for (int k = 0; k < 12; ++k) {
                categories[number_of_categories].montly_sales[k] = 0;
            }

            strcpy(categories[number_of_categories].category_name, products[i].product_category);

            categories[number_of_categories].montly_sales[products[i].sale_date.tm_mon] += products[i].unit_price * products[i].quantity_sold;

            number_of_categories++;
        }
    }

    _print_sales_category_(categories, number_of_categories);

    free(categories);
}