# RSA RPM Lab

Учебная реализация алгоритма RSA на C в двух вариантах:

- `simple` — простая, неоптимизированная реализация;
- `optimized` — оптимизированная реализация возведения в степень по модулю.

Готовые RPM-пакеты находятся в каталоге:

```text
ready-made-package/
```

## 1. Сборка для тестирования

### Simple

```bash
cd simple
make
```

Запуск:

```bash
./rsa-simple -e "Hello"
```

Флаг `-e` — шифрование.

Для дешифрования используется:

```bash
./rsa-simple -d "3000 1313 745 745 2185"
```

Флаг `-d` — дешифрование.

> Дешифрование пока не реализовано и используется как заглушка.

Очистка:

```bash
make clean
```

### Optimized

```bash
cd optimized
make
```

Запуск:

```bash
./rsa-optimized -e "Hello"
```

или:

```bash
./rsa-optimized -d "3000 1313 745 745 2185"
```

Очистка:

```bash
make clean
```

## 2. Сборка RPM-пакета

Для сборки используется `rpmbuild`.

Сборка `rsa-simple`:

```bash
rpmbuild -ba \
  --define "_topdir $PWD/RPM" \
  RPM/SPECS/rsa-simple.spec
```

Сборка `rsa-optimized`:

```bash
rpmbuild -ba \
  --define "_topdir $PWD/RPM" \
  RPM/SPECS/rsa-optimized.spec
```

После сборки пакеты находятся в:

```text
RPM/RPMS/x86_64/
```

Например:

```text
rsa-simple-1.0-alt1.x86_64.rpm
rsa-optimized-1.0-alt1.x86_64.rpm
```

## 3. Установка RPM в систему

Установка `rsa-simple`:

```bash
sudo apt-get install ./RPM/RPMS/x86_64/rsa-simple-1.0-alt1.x86_64.rpm
```

Установка `rsa-optimized`:

```bash
sudo apt-get install ./RPM/RPMS/x86_64/rsa-optimized-1.0-alt1.x86_64.rpm
```

После установки программы доступны непосредственно из системы:

```bash
rsa-simple -e "Hello"
```

```bash
rsa-optimized -e "Hello"
```

Проверить установленный пакет можно командой:

```bash
rpm -qa | grep rsa-
```

Удаление пакета:

```bash
sudo apt-get remove rsa-simple
```

или:

```bash
sudo apt-get remove rsa-optimized
```