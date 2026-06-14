# Medical Clinic Services

System obsługi przychodni medycznej napisany w języku C++. Projekt umożliwia podstawową obsługę pacjentów, lekarzy, wizyt oraz dokumentacji medycznej w aplikacji konsolowej.

## Opis projektu

Medical Clinic Services to aplikacja wspierająca pracę prostej przychodni medycznej. Program został zaprojektowany w podejściu obiektowym, z podziałem na klasy odpowiedzialne za użytkowników systemu, pacjentów, wizyty, dokumentację medyczną oraz logikę zarządzającą.

Projekt powstał jako aplikacja edukacyjna pokazująca wykorzystanie języka C++, organizację kodu w plikach nagłówkowych i źródłowych, pracę z repozytorium GitHub oraz przygotowanie testów jednostkowych dla wybranych funkcjonalności.

## Główne funkcje

- logowanie użytkowników systemu,
- obsługa ról użytkowników, m.in. lekarza i recepcjonisty,
- rejestracja pacjentów,
- wyszukiwanie pacjentów po numerze PESEL,
- wyszukiwanie pacjentów po nazwisku,
- dodawanie wizyt lekarskich,
- zmiana terminu wizyty,
- blokada podwójnej wizyty u tego samego lekarza w tym samym terminie,
- tworzenie dokumentacji medycznej pacjenta,
- pobieranie dokumentacji medycznej przypisanej do pacjenta.

## Technologie

| Obszar | Wykorzystane rozwiązanie |
|---|---|
| Język | C++17 |
| Paradygmat | Programowanie obiektowe |
| Środowiska | Visual Studio Code, Visual Studio |
| Kontrola wersji | Git, GitHub |
| Testy | Testy jednostkowe w C++ |

## Struktura projektu

```text
Medical-Clinic-Services/
├── include/        # Pliki nagłówkowe klas
├── src/            # Pliki implementacyjne
├── tests/          # Testy jednostkowe
└── README.md       # Dokumentacja projektu
```

## Najważniejsze klasy

| Klasa | Odpowiedzialność |
|---|---|
| `ClinicSystem` | Główna klasa łącząca logikę systemu |
| `AuthService` | Obsługa logowania użytkowników |
| `User` | Abstrakcyjna klasa bazowa użytkownika |
| `Doctor` | Reprezentacja lekarza |
| `Receptionist` | Reprezentacja recepcjonisty |
| `Patient` | Dane pacjenta |
| `PatientManager` | Rejestracja i wyszukiwanie pacjentów |
| `Appointment` | Dane wizyty lekarskiej |
| `AppointmentManager` | Zarządzanie wizytami |
| `MedicalRecord` | Dokumentacja medyczna pacjenta |

## Uruchomienie projektu

Przykładowa kompilacja aplikacji z poziomu katalogu głównego projektu:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o medical_clinic
```

Uruchomienie:

```bash
./medical_clinic
```

## Testy jednostkowe

W projekcie przygotowano testy jednostkowe dla wybranych obszarów logiki aplikacji. Testy znajdują się w katalogu `tests/`.

Zakres testów obejmuje m.in.:

- logowanie użytkownika,
- dodawanie pacjenta,
- wyszukiwanie pacjenta po PESEL,
- wyszukiwanie pacjenta po nazwisku,
- blokadę duplikatu PESEL,
- dodawanie i zmianę terminu wizyty,
- blokadę podwójnej wizyty u lekarza,
- tworzenie i pobieranie dokumentacji medycznej.

Przykładowa kompilacja jednego pliku testowego:

```bash
g++ -std=c++17 -Iinclude src/Appointment.cpp src/AppointmentManager.cpp src/AuthService.cpp src/ClinicSystem.cpp src/Doctor.cpp src/MedicalRecord.cpp src/Patient.cpp src/PatientManager.cpp src/Receptionist.cpp src/User.cpp tests/PatientTests.cpp -o PatientTests
```

Uruchomienie testu:

```bash
./PatientTests
```

## Praca z repozytorium

Projekt był rozwijany z wykorzystaniem systemu kontroli wersji Git oraz platformy GitHub. Podczas pracy wykorzystywano branche funkcyjne, commity oraz pull requesty.

Przykładowe obszary prac były prowadzone na branchach związanych z:

- obsługą pacjentów,
- obsługą recepcjonisty,
- systemem kliniki,
- użytkownikami i wizytami,
- testami jednostkowymi.

## Autorzy

- Joanna Łanoszka
- Gracjan Michura
- Jakub Nocula

## Repozytorium

Projekt dostępny jest pod adresem:

[https://github.com/noculajakub/Medical-Clinic-Services](https://github.com/noculajakub/Medical-Clinic-Services)
