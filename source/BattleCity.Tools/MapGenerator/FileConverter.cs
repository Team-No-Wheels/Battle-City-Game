using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace MapGenerator
{
    class FileConverter
    {
        const string    SOURCE_EXT_FILTER           = "*.tmx";

        const string    MAP_IDENTIFIER              = "map";
        const string    TILE_WIDTH_IDENTIFIER       = "tilewidth";
        const string    TILE_HEIGHT_IDENTIFIER      = "tileheight";
        const string    IN_TILES_X_IDENTIFIER       = "width";
        const string    IN_TILES_Y_IDENTIFIER       = "height";
        const string    IMAGE_IDENTIFIER            = "image";
        const string    SOURCE_IDENTIFIER           = "source";
        const string    DATA_IDENTIFIER             = "data";
        const string    ERROR_MALFORMED_XML         = "The XML File is in a different format that this parser expects.";
        const int       MAX_CHARS_FROM_ENTITIES     = 4096;
        const char      COMMA_SEPARATOR             = ',';
        const string    NEWLINE                     = "\n";
        const string    EMPTY_STR                   = "";

        const string    INTEGER_IDENTIFIER          = "integer";
        const string    STRING_IDENTIFIER           = "string";
        const string    CLASS_IDENTIFIER            = "class";
        const string    WORLD_IDENTIFIER            = "world";
        const string    SECTORS_IDENTIFIER          = "sectors";
        const string    SECTOR_IDENTIFIER           = "sector";
        const string    NAME_IDENTIFIER             = "name";
        const string    VALUE_IDENTIFIER            = "value";
        const string    ENTITY_IDENTIFIER           = "entity";
        const string    ENTITIES_IDENTIFIER         = "entities";
        const string    SPRITESHEET_INDENTIFIER     = "spritesheet";
        const string    OUT_TILES_X_IDENTIFIER      = "numtilesX";
        const string    OUT_TILES_Y_IDENTIFIER      = "numtilesY";
        const string    POSITION_X_IDENTIFIER       = "posX";
        const string    POSITION_Y_IDENTIFIER       = "posY";

        public void Convert(string SourceDirectory, string DestinationFileName)
        {
            string[] Files = Directory.GetFiles(SourceDirectory, SOURCE_EXT_FILTER);

            if (Files.Length > 0)
            {
                XmlWriterSettings Settings = new XmlWriterSettings();
                Settings.Indent = true;
                Directory.CreateDirectory(Path.GetDirectoryName(DestinationFileName));
                XmlWriter Writer = XmlWriter.Create(DestinationFileName, Settings);
                Writer.WriteStartDocument();
                {
                    Writer.WriteStartElement(WORLD_IDENTIFIER);
                    {
                        Writer.WriteStartElement(SECTORS_IDENTIFIER);
                        {
                            foreach (var File in Files)
                            {
                                Convert(File, Writer);
                            }
                        }
                        Writer.WriteEndElement();
                    }
                    Writer.WriteEndElement();
                }
                Writer.WriteEndDocument();
                Writer.Close();
            }
        }

        private void Convert(string SourceFile, XmlWriter Writer)
        {
            Dictionary<string, string> MappedData = new Dictionary<string, string>();

            XmlReaderSettings Settings = new XmlReaderSettings();
            Settings.DtdProcessing = DtdProcessing.Parse;
            Settings.MaxCharactersFromEntities = MAX_CHARS_FROM_ENTITIES;
            XmlReader Reader = XmlReader.Create(SourceFile, Settings);

            while (Reader.Read())
            {
                if (Reader.IsStartElement())
                {
                    switch (Reader.Name)
                    {
                        case MAP_IDENTIFIER:
                            {
                                MappedData[IN_TILES_X_IDENTIFIER] = Reader[IN_TILES_X_IDENTIFIER];
                                MappedData[IN_TILES_Y_IDENTIFIER] = Reader[IN_TILES_Y_IDENTIFIER];
                                MappedData[TILE_WIDTH_IDENTIFIER] = Reader[TILE_WIDTH_IDENTIFIER];
                                MappedData[TILE_HEIGHT_IDENTIFIER] = Reader[TILE_HEIGHT_IDENTIFIER];
                            }
                            break;

                        case IMAGE_IDENTIFIER:
                            {
                                MappedData[IMAGE_IDENTIFIER] = Reader[SOURCE_IDENTIFIER];
                            }
                            break;

                        case DATA_IDENTIFIER:
                            {
                                if (Reader.Read())
                                {
                                    MappedData[DATA_IDENTIFIER] = Reader.Value.Trim();
                                }
                            }
                            break;
                    }
                }
            }

            if (!(MappedData.ContainsKey(IN_TILES_X_IDENTIFIER)     && MappedData[IN_TILES_X_IDENTIFIER]    != null
                && MappedData.ContainsKey(IN_TILES_Y_IDENTIFIER)    && MappedData[IN_TILES_Y_IDENTIFIER]    != null
                && MappedData.ContainsKey(TILE_WIDTH_IDENTIFIER)    && MappedData[TILE_WIDTH_IDENTIFIER]    != null
                && MappedData.ContainsKey(TILE_HEIGHT_IDENTIFIER)   && MappedData[TILE_HEIGHT_IDENTIFIER]   != null
                && MappedData.ContainsKey(IMAGE_IDENTIFIER)         && MappedData[IMAGE_IDENTIFIER]         != null
                && MappedData.ContainsKey(DATA_IDENTIFIER)          && MappedData[DATA_IDENTIFIER]          != null
                ))
            {
                throw new System.ApplicationException(ERROR_MALFORMED_XML);
            }
            
            string[] Entities = MappedData[DATA_IDENTIFIER].Replace(NEWLINE, EMPTY_STR).Split(COMMA_SEPARATOR);
            int CurrentPosition = 0;

            Writer.WriteStartElement(SECTOR_IDENTIFIER);
            {
                Writer.WriteAttributeString (NAME_IDENTIFIER,            Path.GetFileNameWithoutExtension(SourceFile));
                Writer.WriteStartElement(STRING_IDENTIFIER);
                {
                    Writer.WriteAttributeString(SPRITESHEET_INDENTIFIER, MappedData[IMAGE_IDENTIFIER]);
                }
                Writer.WriteEndElement();
                Writer.WriteStartElement(INTEGER_IDENTIFIER);
                {
                    Writer.WriteAttributeString(TILE_WIDTH_IDENTIFIER, MappedData[TILE_WIDTH_IDENTIFIER]);
                }
                Writer.WriteEndElement();
                Writer.WriteStartElement(INTEGER_IDENTIFIER);
                {
                    Writer.WriteAttributeString(TILE_HEIGHT_IDENTIFIER, MappedData[TILE_HEIGHT_IDENTIFIER]);
                }
                Writer.WriteEndElement();
                Writer.WriteStartElement(INTEGER_IDENTIFIER);
                {
                    Writer.WriteAttributeString(OUT_TILES_X_IDENTIFIER, MappedData[IN_TILES_X_IDENTIFIER]);
                }
                Writer.WriteEndElement();
                Writer.WriteStartElement(INTEGER_IDENTIFIER);
                {
                    Writer.WriteAttributeString(OUT_TILES_Y_IDENTIFIER, MappedData[IN_TILES_Y_IDENTIFIER]);
                }
                Writer.WriteEndElement();
                Writer.WriteStartElement(ENTITIES_IDENTIFIER);
                {
                    for (int i = 0; i < Int32.Parse(MappedData[IN_TILES_X_IDENTIFIER]); ++i)
                    {
                        for (int j = 0; j < Int32.Parse(MappedData[IN_TILES_Y_IDENTIFIER]); ++j)
                        {
                            Writer.WriteStartElement(ENTITY_IDENTIFIER);
                            {
                                Writer.WriteAttributeString(CLASS_IDENTIFIER, Entities[CurrentPosition]);
                                Writer.WriteStartElement(INTEGER_IDENTIFIER);
                                {
                                    Writer.WriteAttributeString(NAME_IDENTIFIER, POSITION_X_IDENTIFIER);
                                    Writer.WriteAttributeString(VALUE_IDENTIFIER, i.ToString());
                                }
                                Writer.WriteEndElement();

                                Writer.WriteStartElement(INTEGER_IDENTIFIER);
                                {
                                    Writer.WriteAttributeString(NAME_IDENTIFIER, POSITION_Y_IDENTIFIER);
                                    Writer.WriteAttributeString(VALUE_IDENTIFIER, j.ToString());
                                }
                                Writer.WriteEndElement();
                            }
                            Writer.WriteEndElement();
                            ++CurrentPosition;
                        }
                    }
                }
                Writer.WriteEndElement();
            }
            Writer.WriteEndElement();
        }
    }
}
