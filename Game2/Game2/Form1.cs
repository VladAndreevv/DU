using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Game2
{
    public partial class Form1 : Form
    {
        private int rI, rJ;
        private PictureBox Coal; // Объявление переменной угля
        private PictureBox cube; // Объявление переменной персонажа
        private PictureBox stove; // Объявление переменной печи

        private int _width = 400; // Ширина игрового поля
        private int _height = 400; // Высота игрового поля
        private int _sizeOfSides = 40; // Размер квадратов на игровом поле

        private Timer gameTimer = new Timer();
        private int totalTime = 20; // Время по умолчанию
        private int timeLeft;

        private ProgressBar _fuelTimer;

        private int coalCount; // Количество угля на карте
        private int collectedCoalCount; // Количество собранного угля
        private int totalCollectedCoalCount; // Переменная для общего количества собранного угля
        private int bestRecord; // Добавьте это объявление для хранения лучшего рекорда
        private Random random = new Random();

        private NumericUpDown coalSelector; // Для выбора количества угля
        private NumericUpDown timerSelector; // Для выбора времени
        private Button startButton; // Кнопка для начала игры
        private Button exitButton; // Кнопка для выхода из игры
        private Button infoButton; // Кнопка для информации об игре
        private Button colorsButton; // Объявление переменной для кнопки Colors
        private Button bestPlayersButton; // Кнопка для вывода топа игроков
        private Label coalCounterLabel; // Лейбл для отображения счётчика угля
        private Label totalCoalCounterLabel; // Лейбл для отображения общего количества собранного угля
        private Label bestRecordLabel; // Лейбл для отображения лучшего рекорда
        private Label playerNameLabel; // Лейбл для отображения ника игрока
        private Label playerNameButton; // Кнопка для ввода ника игрока
        private Button setNameButton; // Кнопка для установки имени игрока
        private string playerName = " Guest ";

        private int bestGameRecord = 0; // Лучший рекорд за одну игру
        private Dictionary<string, int> playerScores = new Dictionary<string, int>(); // Дириктория для хранения информации о лучших игроках

        private PictureBox bomb; // Переменная для бомбы
        private CheckBox bombCheckBox; // Объявляем bombCheckBox на уровне класса
        private bool isBombEnabled = false; // Флаг для отслеживания включения бомбы

        public Form1()
        {
            InitializeComponent();
            this.Width = _width + 240; // Учитываем ширину для меню
            this.Height = _height + 39; // Учитываем заголовок окна

            //--------------------------------------------------------- Инициализируем прогрессбар
            _fuelTimer = new ProgressBar();
            _fuelTimer.Maximum = totalTime;
            _fuelTimer.Value = totalTime;
            _fuelTimer.Location = new Point(410, 10);
            _fuelTimer.Size = new Size(200, 10);
            _fuelTimer.Visible = false;
            this.Controls.Add(_fuelTimer);

            InitializeMenu(); // Инициализируем меню

            //Настраиваем таймер
            gameTimer.Interval = 1000;
            gameTimer.Tick += OnTimerTick; // Добавляем новый обработчик только один раз
        }
        private void InitializeMenu()
        {   // --------------------------------------------------------- Визуальная часть
            // Лейбл для выбора количества угля
            Label coalLabel = new Label();
            coalLabel.Text = "Coal(1-3 coal):";
            coalLabel.Width = 80;
            coalLabel.Location = new Point(_width + 20, 50);
            this.Controls.Add(coalLabel);

            // Выбор количества угля
            coalSelector = new NumericUpDown();
            coalSelector.Minimum = 1;
            coalSelector.Maximum = 3;
            coalSelector.Width = 60;
            coalSelector.Location = new Point(_width + 100, 50);
            this.Controls.Add(coalSelector);

            // Лейбл для выбора времени
            Label timerLabel = new Label();
            timerLabel.Text = "Time(5-30 sec):";
            timerLabel.Width = 80;
            timerLabel.Location = new Point(_width + 20, 75);
            this.Controls.Add(timerLabel);

            // Выбор времени
            timerSelector = new NumericUpDown();
            timerSelector.Minimum = 5;
            timerSelector.Maximum = 30;
            timerSelector.Width = 60;
            timerSelector.Location = new Point(_width + 100, 75);
            this.Controls.Add(timerSelector);

            // Кнопка для начала игры
            startButton = new Button();
            startButton.Text = "Start Game";
            startButton.Location = new Point(_width + 20, 130);
            startButton.Click += StartButton_Click;
            this.Controls.Add(startButton);

            // Кнопка Exit для выхода из игры
            exitButton = new Button();
            exitButton.Text = "Exit";
            exitButton.Location = new Point(startButton.Location.X + 75, startButton.Location.Y); // Справа от кнопки Start
            exitButton.Click += ExitButton_Click;
            this.Controls.Add(exitButton);

            // Кнопка Info для отображения правил игры
            infoButton = new Button();
            infoButton.Text = "Info(A)";
            infoButton.Location = new Point(startButton.Location.X, startButton.Location.Y + 23); // Под кнопкой Start
            infoButton.Click += InfoButton_Click;
            this.Controls.Add(infoButton);

            // Кнопка Colors для объяснения цвета
            colorsButton = new Button();
            colorsButton.Text = "Colors(Q)";
            colorsButton.Location = new Point(infoButton.Location.X + infoButton.Width + 0, infoButton.Location.Y); // Справа от кнопки Info
            colorsButton.Click += ColorsButton_Click; // Подключаем обработчик событий
            this.Controls.Add(colorsButton);

            // Кнопка для вывода топа лучших игроков
            bestPlayersButton = new Button();
            bestPlayersButton.Text = "Show Best Players";
            bestPlayersButton.Location = new Point(startButton.Location.X, startButton.Location.Y + 50); // Под кнопкой старт
            bestPlayersButton.Click += BestPlayersButton_Click; // Обработчик
            this.Controls.Add(bestPlayersButton);

            // Лейбл для отображения имени игрока. Изначально игрок числится как "Guest"
            playerNameLabel = new Label();
            playerNameLabel.Text = $"Your name is '{playerName}'";
            playerNameLabel.Location = new Point(_width + 20, 275);
            playerNameLabel.Width = 180;
            this.Controls.Add(playerNameLabel);

            // Кнопка для вызова диалогового окна для ввода имени
            setNameButton = new Button();
            setNameButton.Text = "Set Name";
            setNameButton.Location = new Point(_width + 20, 300);
            setNameButton.Click += SetNameButton_Click; // Добавляем обработчик
            this.Controls.Add(setNameButton);

            // Лейбл для отображения счётчика собранного угля (В инвентаре)
            coalCounterLabel = new Label();
            coalCounterLabel.Text = "Collected Coal: 0";
            coalCounterLabel.Location = new Point(_width + 20, 250); // Позиция под настройками
            this.Controls.Add(coalCounterLabel);

            // Лейбл для отображения общего количества собранного угля
            totalCoalCounterLabel = new Label();
            totalCoalCounterLabel.Text = "In Total: 0";
            totalCoalCounterLabel.Location = new Point(_width + 20, 210);
            this.Controls.Add(totalCoalCounterLabel);

            // Лейбл для лучшего рекорда
            bestRecordLabel = new Label();
            bestRecordLabel.Text = "Best Record: 0"; // Изначально 0
            bestRecordLabel.Location = new Point(_width + 20, 231); // Под общим счётчиком
            this.Controls.Add(bestRecordLabel);

            // Чекбокс для включения бомб
            bombCheckBox = new CheckBox();
            bombCheckBox.Text = "Enable Bombs";
            bombCheckBox.Location = new Point(_width + 25, 100);  // Под меткой лучшего рекорда
            this.Controls.Add(bombCheckBox);
        }
        
        public static class Prompt
        {//----------------------------------------------------------- Вспомогательное окно для ввода никнейма
            public static string ShowDialog(string text, string caption)
            {
                Form prompt = new Form()
                {
                    Width = 240,
                    Height = 120,
                    FormBorderStyle = FormBorderStyle.FixedDialog,
                    Text = caption,
                    StartPosition = FormStartPosition.CenterScreen
                };

                Label textLabel = new Label() { Left = 10, Top = 10, Text = text };
                TextBox inputBox = new TextBox() { Left = 10, Top = 35, Width = 200 };
                Button confirmation = new Button() { Text = "Confirm", Left = 135, Width = 75, Top = 10 };

                confirmation.Click += (sender, e) => { prompt.Close(); };

                prompt.Controls.Add(confirmation);
                prompt.Controls.Add(textLabel);
                prompt.Controls.Add(inputBox);
                prompt.AcceptButton = confirmation;

                prompt.ShowDialog();

                return inputBox.Text;
            }
        }
        private void SetNameButton_Click(object sender, EventArgs e)
        {   //-------------------------------------------------------- Кнопка "Указать Никнейм"
            string newName = Prompt.ShowDialog("Enter your name:", "Set Name");

            if (!string.IsNullOrWhiteSpace(newName))
            {
                playerName = newName;
                playerNameLabel.Text = $"Your name is ' {playerName} '"; // Обновляем лейбл
            }
        }
        private void BestPlayersButton_Click(object sender, EventArgs e)
        {   //-------------------------------------------------------- Кнопка для вывода лучших игроков (Не учитывает Guest!!)
            // Сортируем игроков по общему количеству угля (totalCollectedCoalCount)
            var topPlayers = playerScores
                .Where(p => p.Key != " Guest ") // Исключаем гостевых игроков
                .OrderByDescending(p => p.Value) // Сортируем по общему количеству собранного угля
                .Take(10) // Берем топ-10 игроков
                .ToList();

            // Строим строку с именами и очками игроков
            string topPlayersMessage = "Top Players:\n\n";
            foreach (var player in topPlayers)
            {
                topPlayersMessage += $"{player.Key}: {player.Value} coal\n"; // Отображаем общее количество угля для каждого игрока
            }

            if (topPlayers.Count == 0)
            {
                topPlayersMessage = "No players yet!";
            }

            // Выводим сообщение с топом игроков
            MessageBox.Show(topPlayersMessage, "Top Players");
        }
        private void StartButton_Click(object sender, EventArgs e)
        {   //--------------------------------------------------------- Кнопка "Старт"
            // Получаем значения из меню
            coalCount = (int)coalSelector.Value;
            totalTime = (int)timerSelector.Value;
            timeLeft = totalTime; // Убедитесь, что timeLeft инициализируется правильно

            // Устанавливаем значения для прогрессбара
            _fuelTimer.Maximum = totalTime;
            _fuelTimer.Value = totalTime; // Прогрессбар устанавливается в полное значение

            // Очищаем старую игру
            ClearOldGame();

            // Инициализируем персонажа (куб)
            cube = new PictureBox();
            cube.BackColor = Color.Red;
            cube.Size = new Size(_sizeOfSides, _sizeOfSides);
            cube.Location = new Point(0, 0);  // Начальная позиция
            this.Controls.Add(cube);

            // Генерация карты и угля
            _generateMap();
            _generateCoal();
            _generateStove(); // Генерация печи

            isBombEnabled = bombCheckBox.Checked;

            if (isBombEnabled)
            {
                _generateBomb(); // Генерируем бомбу, если включены
            }

            // Запускаем таймер
            gameTimer.Start(); // Теперь таймер должен стартовать с правильным значением

            // Добавляем обработчик клавиш
            this.KeyDown += OKP;

            // Отключаем настройки
            DisableSettings();
        }

        private void ExitButton_Click(object sender, EventArgs e)
        {   //--------------------------------------------------------- Кнопка Выход
            Application.Exit();
        }

        private void InfoButton_Click(object sender, EventArgs e)
        {   //--------------------------------------------------------- Кнопка Информация
            MessageBox.Show("\nRules of the game:\n1. Collect coal on the map. \n2. Carry the coal to the furnace to replenish the time.\n3. The game ends when the time runs out.\n\nVladislav Andreev - the creator of this game.");
        }

        // Обработчик события для кнопки Colors
        private void ColorsButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Explanation of colors:\n- Black: Coal\n- Brown: Stove\n- Red: Player\n- Green: Bomb\n\nUse these colors to understand your game elements better.");
        }

        private void UpdatePlayerScore()
        {
            // Проверяем и обновляем общий счёт игрока (totalCollectedCoalCount)
            if (!playerScores.ContainsKey(playerName))
            {
                playerScores.Add(playerName, totalCollectedCoalCount); // Добавляем нового игрока с его общим счётом
            }
            else
            {
                // Обновляем общий счёт, если новое значение больше
                playerScores[playerName] = totalCollectedCoalCount;
            }

            // Обновляем отображение общего счёта на экране
            totalCoalCounterLabel.Text = $"In Total: {totalCollectedCoalCount}";

            // Обновляем лучший результат (для отображения)
            bestRecordLabel.Text = $"Best Record: {totalCollectedCoalCount}"; // Показываем лучший общий рекорд
        }
            private void ClearOldGame()
        {   //---------------------------------------------------------- Функция для очистки предыдущей игры и подведения результатов
            gameTimer.Stop(); // Останавливаем таймер
            timeLeft = totalTime; // Сбрасываем оставшееся время
            _fuelTimer.Value = totalTime; // Сбрасываем прогрессбар
            UpdatePlayerScore(); // Обновляем информацию о рекорде

            // Удаляем персонажа
            if (cube != null)
            {
                this.Controls.Remove(cube);
                cube = null;
            }

            // Удаляем печь
            if (stove != null)
            {
                this.Controls.Remove(stove);
                stove = null;
            }

            // Удаляем бомбу
            if (bomb != null)
            {
                this.Controls.Remove(bomb);
                bomb = null; // Сбрасываем ссылку на бомбу
            }

            // Очищаем все угли и сетку перед новой игрой
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                Control control = this.Controls[i];
                if (control is PictureBox && (control.BackColor == Color.Black || control.BackColor == Color.Gray || control.BackColor == Color.Red || control.BackColor == Color.Brown))
                {
                    this.Controls.Remove(control);
                }
            }

            // Удаляем обработчик KeyDown (Управление)
            this.KeyDown -= OKP;

            // Сбрасываем счётчик угля
            collectedCoalCount = 0;
            coalCounterLabel.Text = "Collected Coal: 0"; // Сбрасываем текст лейбла

            totalCollectedCoalCount = 0;
            totalCoalCounterLabel.Text = "In Total: 0"; // Этот тоже сбрасываем
        }

        private void _generateCoal()
        {//------------------------------------------------------ Функция для генерации угля на карте
            for (int i = 0; i < coalCount; i++)
            {
                // Генерация позиции
                rI = (random.Next(0, _width / _sizeOfSides) * _sizeOfSides);
                rJ = (random.Next(0, _height / _sizeOfSides) * _sizeOfSides);

                Coal = new PictureBox();
                Coal.BackColor = Color.Black;
                Coal.Size = new Size(_sizeOfSides, _sizeOfSides);
                Coal.Location = new Point(rI, rJ);
                this.Controls.Add(Coal);
            }
        }

        private void _generateStove()
        {//------------------------------------------------------ Функция для генерации печи на карте
            // Генерация позиции печи
            rI = (random.Next(0, _width / _sizeOfSides) * _sizeOfSides);
            rJ = (random.Next(0, _height / _sizeOfSides) * _sizeOfSides);

            stove = new PictureBox();
            stove.BackColor = Color.Brown; // Цвет печи
            stove.Size = new Size(_sizeOfSides, _sizeOfSides);
            stove.Location = new Point(rI, rJ);
            this.Controls.Add(stove);
        }

        private void _generateBomb()
        {
            int attempts = 0;
            const int maxAttempts = 100;
            bool positionFound = false;
            Point bombPosition = Point.Empty;

            do
            {
                // Генерация случайной позиции для бомбы
                rI = (random.Next(0, _width / _sizeOfSides) * _sizeOfSides);
                rJ = (random.Next(0, _height / _sizeOfSides) * _sizeOfSides);
                bombPosition = new Point(rI, rJ);

                // Проверка, допустима ли эта позиция
                if (IsPositionValid(bombPosition))
                {
                    positionFound = true;
                }

                attempts++;
            } while (!positionFound && attempts < maxAttempts);

            if (positionFound)
            {
                // Создание и отображение бомбы
                bomb = new PictureBox();
                bomb.BackColor = Color.Green; // Цвет бомбы
                bomb.Size = new Size(_sizeOfSides, _sizeOfSides);
                bomb.Location = bombPosition;
                this.Controls.Add(bomb);
            }
            else
            {
                // Сообщение об ошибке при превышении лимита попыток
                MessageBox.Show("Failed to generate bomb position after 100 attempts.");
            }
        }
        private void MoveBomb()
        {
            if (bomb != null)
            {
                Point newPosition;
                int attempts = 0;
                const int maxAttempts = 100;
                do
                {
                    rI = (random.Next(0, _width / _sizeOfSides) * _sizeOfSides);
                    rJ = (random.Next(0, _height / _sizeOfSides) * _sizeOfSides);
                    newPosition = new Point(rI, rJ);
                    attempts++;
                } while (!IsPositionValid(newPosition) && attempts < maxAttempts);

                if (attempts < maxAttempts)
                {
                    bomb.Location = newPosition; // Перемещаем бомбу
                }
                else
                {
                    MessageBox.Show("Failed to move bomb after 100 attempts.");
                }
            }
        }
        private void _generateMap()
        {//------------------------------------------------------ Функция для генерации самой карты
            // Генерация горизонтальных линий
            for (int i = 0; i <= _height / _sizeOfSides; i++)
            {
                PictureBox pic = new PictureBox();
                pic.BackColor = Color.Gray;
                pic.Location = new Point(0, _sizeOfSides * i);
                pic.Size = new Size(_width, 1);
                this.Controls.Add(pic);
            }

            // Генерация вертикальных линий
            for (int i = 0; i <= _width / _sizeOfSides; i++)
            {
                PictureBox pic = new PictureBox();
                pic.BackColor = Color.Gray;
                pic.Location = new Point(_sizeOfSides * i, 0);
                pic.Size = new Size(1, _height);
                this.Controls.Add(pic);
            }
        }

        private void OKP(object sender, KeyEventArgs e)
        {
            //------------------------------------------------------ Управление персонажем
            switch (e.KeyCode)
            {
                case Keys.Up:
                    if (cube.Top > 0)
                    {
                        cube.Top -= _sizeOfSides;
                    }
                    break;
                case Keys.Down:
                    if (cube.Bottom < _height)
                    {
                        cube.Top += _sizeOfSides;
                    }
                    break;
                case Keys.Left:
                    if (cube.Left > 0)
                    {
                        cube.Left -= _sizeOfSides;
                    }
                    break;
                case Keys.Right:
                    if (cube.Right < _width)
                    {
                        cube.Left += _sizeOfSides;
                    }
                    break;
                case Keys.A: // Добавляем обработку клавиши "A"
                    InfoButton_Click(this, EventArgs.Empty); // Вызываем метод InfoButton_Click
                    break;
                case Keys.Q: // Добавляем обработку клавиши "C" для кнопки Colors
                    ColorsButton_Click(this, EventArgs.Empty); // Вызываем метод ColorsButton_Click
                    break;
            }

            //--------------------------------------------------------- Проверка пересечения с углём
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                Control control = this.Controls[i];
                if (control is PictureBox && control.BackColor == Color.Black && cube.Bounds.IntersectsWith(control.Bounds))
                {
                    this.Controls.Remove(control); // Персонаж собирает уголь
                    collectedCoalCount++; // Увеличиваем счётчик собранного угля
                    totalCollectedCoalCount++; // Увеличиваем общий счётчик собранного угля
                    coalCounterLabel.Text = $"Collected Coal: {collectedCoalCount}"; // Обновляем текст лейбла
                    totalCoalCounterLabel.Text = $"In Total: {totalCollectedCoalCount}"; // Обновляем текст общего счётчика
                    AddNewCoal(); // Генерируем новый уголь

                    // Проверяем, включена ли бомба и перемещаем её
                    if (isBombEnabled && bomb != null)
                    {
                        MoveBomb(); // Перемещаем бомбу в новое место
                    }

                    break;
                }

                //----------------------------------------------------- Проверка пересечения с печью
                if (control is PictureBox && control.BackColor == Color.Brown && cube.Bounds.IntersectsWith(control.Bounds))
                {
                    // Пополняем прогрессбар
                    int addedTime = collectedCoalCount;
                    _fuelTimer.Value = Math.Min(_fuelTimer.Value + addedTime, _fuelTimer.Maximum);

                    // Обновляем переменную timeLeft
                    timeLeft = Math.Min(timeLeft + addedTime, _fuelTimer.Maximum);

                    // Сбрасываем количество собранного угля
                    collectedCoalCount = 0;
                    coalCounterLabel.Text = $"Collected Coal: {collectedCoalCount}"; // Обновляем текст лейбла
                    break;
                }
            }

            //--------------------------------------------------------- Проверка пересечения с бомбой
            if (isBombEnabled && bomb != null && cube.Bounds.IntersectsWith(bomb.Bounds))
            {
                gameTimer.Stop(); // Останавливаем игру
                MessageBox.Show("You hit a bomb! Game over.");
                EnableSettings();
                return; // Прерываем дальнейшее выполнение, так как игра окончена
            }
        }

        private void AddNewCoal()
        {//---------------------------------------------Добовление нового угля на карту
            rI = (random.Next(0, _width / _sizeOfSides) * _sizeOfSides);
            rJ = (random.Next(0, _height / _sizeOfSides) * _sizeOfSides);

            Coal = new PictureBox();
            Coal.BackColor = Color.Black;
            Coal.Size = new Size(_sizeOfSides, _sizeOfSides);
            Coal.Location = new Point(rI, rJ);
            this.Controls.Add(Coal);
        }

        private void OnTimerTick(object sender, EventArgs e)
        {
            if (timeLeft > 0)
            {
                timeLeft--; // Уменьшаем оставшееся время на 1 секунду
                _fuelTimer.Value = timeLeft; // Обновляем прогрессбар
            }
            else
            {
                gameTimer.Stop(); // Останавливаем таймер

                // Проверяем, побили ли мы лучший рекорд (В конце игры)
                if (totalCollectedCoalCount > bestRecord)
                {
                    bestRecord = totalCollectedCoalCount; // Обновляем лучший рекорд
                    bestRecordLabel.Text = $"Best Record: {bestRecord}"; // Обновляем метку лучшего рекорда
                }

                MessageBox.Show("Time's up! Game over.");
                EnableSettings(); // Включаем настройки
            }
        }
        private bool IsPositionValid(Point position)
        {
            Rectangle bombRect = new Rectangle(position, new Size(_sizeOfSides, _sizeOfSides));

            foreach (Control control in this.Controls)
            {
                if (control is PictureBox)
                {
                    // Проверяем, что объект не является сеткой (горизонтальными и вертикальными линиями)
                    if (control.BackColor == Color.Gray)
                    {
                        continue; // Игнорируем сетку
                    }

                    Rectangle controlRect = control.Bounds;
                    if (controlRect.IntersectsWith(bombRect) && control != bomb)
                    {
                        return false; // Позиция недействительна, если пересекается с другим объектом
                    }
                }
            }

            return true; // Позиция действительна
        }
        //---------------------------------------------------------------------- Включение/выключение интерфейса
        private void EnableSettings()
        {
            coalSelector.Enabled = true;  // Включаем выбор угля
            timerSelector.Enabled = true; // Включаем выбор времени
            _fuelTimer.Visible = false;   // Выключаем видимость игрового таймера
            bombCheckBox.Enabled = true;  // Включаем кнопку включения игры с бомбами
            startButton.Enabled = true;   // Включаем кнопку начала игры
            exitButton.Enabled = true;    // Включаем кнопку выхода
            infoButton.Enabled = true;    // Включаем кнопку информации
            colorsButton.Enabled = true;
            setNameButton.Enabled = true;
            bestPlayersButton.Enabled = true;
        }
        private void DisableSettings()
        {
            coalSelector.Enabled = false; // Отключаем выбор угля
            timerSelector.Enabled = false; // Отключаем выбор времени
            _fuelTimer.Visible = true;    // Включаем видимость игрового таймера
            bombCheckBox.Enabled = false; // Отключаем кнопку включения игры с бомбами
            startButton.Enabled = false; // Отключаем кнопку начала игры
            exitButton.Enabled = false;  // Отключаем кнопку выхода
            infoButton.Enabled = false;  // Отключаем кнопку информации
            colorsButton.Enabled = false;
            setNameButton.Enabled = false;
            bestPlayersButton.Enabled = false;
        }
    }
}