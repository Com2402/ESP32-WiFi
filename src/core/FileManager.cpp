#include "FileManager.h"
// FileManager fileManager;
void FileManager::init()
{
  if (!SPIFFS.begin(true))
  {
    // Serial.println("An error has occurred while mounting LittleFS");
    return;
  }
  // Serial.println("File mounted successfully");
  listDir(SPIFFS, "/", 3); // List the directories up to one level beginning at the root directory
}

// Read File from SPIFFS
String FileManager::readFile(fs::FS &fs, const char *path)
{
  // Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    // Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while (file.available())
  {
    fileContent += (char)file.read(); // file.readStringUntil('\n');
    // break;
  }
  file.close();
  return fileContent;
}

// Write file to SPIFFS
void FileManager::writeFile(fs::FS &fs, const char *path, const char *message)
{
  // Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    // Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    // Serial.println("- file written");
  }
  else
  {
    // Serial.println("- frite failed");
  }
  file.close();
}

void FileManager::listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
  // Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root)
  {
    // Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory())
  {
    // Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      // Serial.print("  DIR : ");
      // Serial.println(file.name());
      if (levels)
      {
        listDir(fs, file.path(), levels - 1);
      }
    }
    else
    {
      // Serial.print("  FILE: ");
      // Serial.print(file.name());
      // Serial.print("\tSIZE: ");
      // Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void FileManager::createDir(fs::FS &fs, const char *path)
{
  // Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path))
  {
    // Serial.println("Dir created");
  }
  else
  {
    // Serial.println("mkdir failed");
  }
}

void FileManager::removeDir(fs::FS &fs, const char *path)
{
  // Serial.printf("Removing Dir: %s\n", path);
  if (fs.rmdir(path))
  {
    // Serial.println("Dir removed");
  }
  else
  {
    // Serial.println("rmdir failed");
  }
}

void FileManager::appendFile(fs::FS &fs, const char *path, const char *message)
{
  // Serial.printf("Appending to file: %s\r\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    // Serial.println("- failed to open file for appending");
    return;
  }
  if (file.print(message))
  {
    // Serial.println("- message appended");
  }
  else
  {
    // Serial.println("- append failed");
  }
  file.close();
}