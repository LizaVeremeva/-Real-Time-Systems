#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;

const int SIMULATION_DAYS = 5;
const int MAX_NUGGETS_PER_FATMAN = 10000;
const int INITIAL_NUGGETS = 3000;
const int MEALS_PER_DAY = 4;

struct ExperimentResult {
    int gluttony;
    int efficiency_factor;
    string description;
};

void demonstrate_experiment(int gluttony, int efficiency_factor, const string& description) {
    cout << "\n\n" << string(50, '=') << endl;
    cout << "ЭКСПЕРИМЕНТ: " << description << endl;
    cout << "Коэффициенты: gluttony=" << gluttony
        << ", efficiency_factor=" << efficiency_factor << endl;
    cout << "Приемов пищи в день: " << MEALS_PER_DAY << endl;
    cout << string(50, '=') << endl;

    int dishes[3] = { INITIAL_NUGGETS, INITIAL_NUGGETS, INITIAL_NUGGETS };
    int eaten[3] = { 0, 0, 0 };
    bool alive[3] = { true, true, true };

    cout << "Начальные условия:" << endl;
    cout << "- В каждой тарелке: " << INITIAL_NUGGETS << " наггетсов" << endl;
    cout << "- Максимум на толстяка: " << MAX_NUGGETS_PER_FATMAN << " наггетсов" << endl;
    cout << "- Длительность: 5 дней" << endl;

    for (int day = 1; day <= SIMULATION_DAYS; day++) {
        cout << "\n--- День " << day << " ---" << endl;

        // Кук готовит
        for (int i = 0; i < 3; i++) {
            dishes[i] += efficiency_factor;
        }
        cout << "Кук приготовил: +" << efficiency_factor << " наггетсов в каждую тарелку" << endl;

        // Толстяки едят
        int daily_eaten[3] = { 0, 0, 0 };
        for (int meal = 0; meal < MEALS_PER_DAY; meal++) {
            for (int i = 0; i < 3; i++) {
                if (!alive[i]) continue;

                if (dishes[i] >= gluttony) {
                    dishes[i] -= gluttony;
                    eaten[i] += gluttony;
                    daily_eaten[i] += gluttony;

                    if (eaten[i] >= MAX_NUGGETS_PER_FATMAN) {
                        alive[i] = false;
                        cout << "  Толстяк " << (i + 1) << " съел " << eaten[i]
                            << " наггетсов и САМОУНИЧТОЖИЛСЯ!" << endl;
                    }
                }
                else if (dishes[i] > 0) {
                    cout << "  Толстяк " << (i + 1) << " хочет " << gluttony
                        << ", но в тарелке только " << dishes[i] << "!" << endl;
                    cout << "\n" << string(20, '=') << " РЕЗУЛЬТАТ: КУКА УВОЛИЛИ! "
                        << string(20, '=') << endl;
                    cout << "Не хватило наггетсов до истечения 5 дней." << endl;
                    return;
                }
                else {
                    cout << "  Тарелка толстяка " << (i + 1) << " ПУСТА!" << endl;
                    cout << "\n" << string(20, '=') << " РЕЗУЛЬТАТ: КУКА УВОЛИЛИ! "
                        << string(20, '=') << endl;
                    cout << "Наггетсы закончились." << endl;
                    return;
                }
            }
        }

        cout << "Состояние после дня " << day << ":" << endl;
        cout << "  Наггетсов в тарелках: " << dishes[0] << ", " << dishes[1] << ", " << dishes[2] << endl;
        cout << "  Съедено сегодня: " << daily_eaten[0] << ", " << daily_eaten[1] << ", " << daily_eaten[2] << endl;
        cout << "  Всего съедено: " << eaten[0] << ", " << eaten[1] << ", " << eaten[2] << endl;

        if (!alive[0] && !alive[1] && !alive[2]) {
            cout << "\n" << string(20, '=') << " РЕЗУЛЬТАТ: КУК БЕЗ ЗАРПЛАТЫ! "
                << string(20, '=') << endl;
            cout << "Все толстяки самоуничтожились до истечения 5 дней." << endl;
            return;
        }
    }

    cout << "\n" << string(20, '=') << " РЕЗУЛЬТАТ: КУК УВОЛИЛСЯ САМ! "
        << string(20, '=') << endl;
    cout << "Прошло 5 дней работы." << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << string(50, '=') << endl;
    cout << "Лабораторная работа №4: Три толстяка" << endl;
    cout << string(50, '=') << endl;
    cout << "ФИНАЛЬНАЯ ДЕМОНСТРАЦИЯ ТРЕХ СЦЕНАРИЕВ" << endl;
    cout << string(50, '=') << endl;

    // Идеально подобранные коэффициенты для трех сценариев
    vector<ExperimentResult> experiments = {
        {180, 15, "СЦЕНАРИЙ 1: Кука увольняют"},
        {500, 1400, "СЦЕНАРИЙ 2: Кук без зарплаты"},
        {30, 100, "СЦЕНАРИЙ 3: Кук уволился сам"}
    };

    cout << "\nИСПОЛЬЗУЕМЫЕ КОЭФФИЦИЕНТЫ:" << endl;
    cout << string(50, '-') << endl;
    for (size_t i = 0; i < experiments.size(); i++) {
        cout << experiments[i].description << ":" << endl;
        cout << "  gluttony = " << experiments[i].gluttony << endl;
        cout << "  efficiency_factor = " << experiments[i].efficiency_factor << endl;
        cout << "  Приемов пищи в день: " << MEALS_PER_DAY << endl;

        // Расчет для понимания
        int daily_eaten = experiments[i].gluttony * MEALS_PER_DAY;
        int daily_cooked = experiments[i].efficiency_factor;
        int daily_change = daily_cooked - daily_eaten;

        cout << "  Съедают в день: " << daily_eaten << " наггетсов" << endl;
        cout << "  Готовят в день: " << daily_cooked << " наггетсов" << endl;
        cout << "  Изменение в день: " << (daily_change >= 0 ? "+" : "") << daily_change << " наггетсов" << endl;
        cout << string(50, '-') << endl;
    }

    // Демонстрация
    for (size_t i = 0; i < experiments.size(); i++) {
        demonstrate_experiment(experiments[i].gluttony,
            experiments[i].efficiency_factor,
            experiments[i].description);
    }

    cout << "\n\n" << string(50, '=') << endl;
    cout << "ВЫВОДЫ И АНАЛИЗ" << endl;
    cout << string(50, '=') << endl;

    cout << "\n1. КУКА УВОЛИЛИ (gluttony=180, efficiency=15):" << endl;
    cout << "   - Толстяки съедают: 180 * 4 = 720 наггетсов в день" << endl;
    cout << "   - Кук готовит: 15 наггетсов в день" << endl;
    cout << "   - Ежедневная убыль: 720 - 15 = 705 наггетсов" << endl;
    cout << "   - Начальный запас 3000 закончится через: 3000 / 705 ≈ 4.25 дня" << endl;
    cout << "   - РЕЗУЛЬТАТ: Тарелки опустеют ДО 5 дней" << endl;

    cout << "\n2. КУК БЕЗ ЗАРПЛАТЫ (gluttony=500, efficiency=1400):" << endl;
    cout << "   - Толстяки съедают: 500 * 4 = 2000 наггетсов в день" << endl;
    cout << "   - Кук готовит: 1400 наггетсов в день" << endl;
    cout << "   - Ежедневная убыль: 2000 - 1400 = 600 наггетсов" << endl;
    cout << "   - За 5 дней съедят: 2000 * 5 = 10000 наггетсов (порог самоуничтожения)" << endl;
    cout << "   - За 5 дней тарелки опустеют: 3000 - 600*5 = 0 наггетсов" << endl;
    cout << "   - РЕЗУЛЬТАТ: Толстяки самоуничтожатся как раз на 5-й день" << endl;

    cout << "\n3. КУК УВОЛИЛСЯ САМ (gluttony=30, efficiency=100):" << endl;
    cout << "   - Толстяки съедают: 30 * 4 = 120 наггетсов в день" << endl;
    cout << "   - Кук готовит: 100 наггетсов в день" << endl;
    cout << "   - Ежедневный прирост: 100 - 120 = -20 наггетсов (небольшая убыль)" << endl;
    cout << "   - За 5 дней съедят: 120 * 5 = 600 наггетсов (далеко до 10000)" << endl;
    cout << "   - После 5 дней останется: 3000 - 20*5 = 2900 наггетсов" << endl;
    cout << "   - РЕЗУЛЬТАТ: Проходит 5 дней, толстяки живы, наггетсы остались" << endl;

    cout << "\n" << string(50, '=') << endl;
    cout << "ЗАДАНИЕ ВЫПОЛНЕНО:" << endl;
    cout << "Найдены коэффициенты для трех различных исходов:" << endl;
    cout << "1. Кука увольняют - gluttony=180, efficiency_factor=15" << endl;
    cout << "2. Кук не получает зарплату - gluttony=500, efficiency_factor=1400" << endl;
    cout << "3. Кук увольняется сам - gluttony=30, efficiency_factor=100" << endl;
    cout << string(50, '=') << endl;

    return 0;
}