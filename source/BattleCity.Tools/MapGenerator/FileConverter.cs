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
        const string    ERROR_DEFINITIONS_NOT_FOUND = "Definitions file was not found!";
        const int       MAX_CHARS_FROM_ENTITIES     = 4096;
        const char      COMMA_SEPARATOR             = ',';
        const string    NEWLINE                     = "\n";
        const string    EMPTY_STR                   = "";

        const string    INTEGER_IDENTIFIER          = "integer";
        const string    STRING_IDENTIFIER           = "string";
        const string    VECTOR_IDENTIFIER           = "vector";
        const string    CLASS_IDENTIFIER            = "class";
        const string    WORLD_IDENTIFIER            = "world";
        const string    SECTORS_IDENTIFIER          = "sectors";
        const string    SECTOR_IDENTIFIER           = "sector";
        const string    NAME_IDENTIFIER             = "name";
        const string    VALUE_IDENTIFIER            = "value";
        const string    ENTITY_IDENTIFIER           = "entity";
        const string    SPRITESHEET_INDENTIFIER     = "spritesheet";
        const string    OUT_TILES_X_IDENTIFIER      = "numtilesX";
        const string    OUT_TILES_Y_IDENTIFIER      = "numtilesY";
        const string    POSITION_X_IDENTIFIER       = "posX";
        const string    POSITION_Y_IDENTIFIER       = "posY";
        const string    X_IDENTIFIER                = "x";
        const string    Y_IDENTIFIER                = "y";
        const string    Z_IDENTIFIER                = "z";
        const string    W_IDENTIFIER                = "w";
        const string    WIDTH_IDENTIFIER            = "width";
        const string    HEIGHT_IDENTIFIER           = "height";

        const string    OBJECT_IDENTIFIER           = "object";
        const string    PROPERTY_IDENTIFIER         = "property";
        const string    FRAMEMANAGER_IDENTIFIER     = "FrameManager";
        const string    FRAME_IDENTIFIER            = "Frame";
        const string    ID_IDENTIFIER               = "id";
        const string    POSITION_IDENTIFIER         = "Position";

        const string    BATTLE_CITY                 = "BattleCity";
        const string    DEFINITIONS_FILE            = "Definitions.tmx";
        const string    ZERO                        = "0";

        const float     BOUNDING_BOX_TOLERANCE      = 0.5f;

        Dictionary<string, SpriteData> SpriteMappedData = new Dictionary<string, SpriteData>();

        class SpriteData
        {
            public string id;
            public string classname;
            public float x;
            public float y;
            public float w;
            public float h;

            public SpriteData(string ID, float X, float Y, float W, float H)
            {
                id  = ID;
                x   = X;
                y   = Y;
                w   = W;
                h   = H;
            }

            public bool Intersects(float otherx, float othery, float otherw, float otherh)
            {
                return
                       (Math.Abs(x - otherx) * 2 <= (w + otherw))
                   && (Math.Abs(y - othery) * 2 <= (h + otherh));
            }
        }

        private void WriteSpriteData(string DefinitionsFile, XmlWriter Writer)
        {
            string SpriteSheetName = "";

            XmlReaderSettings Settings = new XmlReaderSettings();
            Settings.DtdProcessing = DtdProcessing.Parse;
            Settings.MaxCharactersFromEntities = MAX_CHARS_FROM_ENTITIES;
            XmlReader Reader = XmlReader.Create(DefinitionsFile, Settings);

            string CurrentElement = "";
            while (Reader.Read())
            {
                if (Reader.IsStartElement())
                {
                    switch (Reader.Name)
                    {
                        case IMAGE_IDENTIFIER:
                            {
                                SpriteSheetName = Path.GetFileName(Reader[SOURCE_IDENTIFIER]);
                            }
                            break;

                        case OBJECT_IDENTIFIER:
                            {
                                CurrentElement = Reader[NAME_IDENTIFIER];
                                SpriteMappedData[CurrentElement]
                                    = new SpriteData(
                                        Reader[ID_IDENTIFIER],
                                        float.Parse(Reader[X_IDENTIFIER]),
                                        float.Parse(Reader[Y_IDENTIFIER]),
                                        float.Parse(Reader[WIDTH_IDENTIFIER]),
                                        float.Parse(Reader[HEIGHT_IDENTIFIER])
                                      );
                            }
                            break;

                        case PROPERTY_IDENTIFIER:
                            {
                                if (Reader[NAME_IDENTIFIER] == CLASS_IDENTIFIER)
                                {
                                    SpriteMappedData[CurrentElement].classname = Reader[VALUE_IDENTIFIER];
                                }
                            }
                            break;
                    }
                }
            }

            Reader.Close();

            Writer.WriteStartElement(ENTITY_IDENTIFIER);
            {
                Writer.WriteAttributeString(CLASS_IDENTIFIER, FRAMEMANAGER_IDENTIFIER);
                Writer.WriteAttributeString(NAME_IDENTIFIER, FRAMEMANAGER_IDENTIFIER);
                Writer.WriteStartElement(STRING_IDENTIFIER);
                {
                    Writer.WriteAttributeString(NAME_IDENTIFIER, SPRITESHEET_INDENTIFIER);
                    Writer.WriteAttributeString(VALUE_IDENTIFIER, SpriteSheetName);
                }
                Writer.WriteEndElement();
                foreach (var Pair in SpriteMappedData)
                {
                    Writer.WriteStartElement(ENTITY_IDENTIFIER);
                    {
                        Writer.WriteAttributeString(CLASS_IDENTIFIER, FRAME_IDENTIFIER);
                        Writer.WriteAttributeString(NAME_IDENTIFIER, Pair.Key);
                        Writer.WriteStartElement(INTEGER_IDENTIFIER);
                        {
                            Writer.WriteAttributeString(NAME_IDENTIFIER, ID_IDENTIFIER);
                            Writer.WriteAttributeString(VALUE_IDENTIFIER, Pair.Value.id);
                        }
                        Writer.WriteEndElement();
                        Writer.WriteStartElement(VECTOR_IDENTIFIER);
                        {
                            Writer.WriteAttributeString(NAME_IDENTIFIER, POSITION_IDENTIFIER);
                            Writer.WriteAttributeString(X_IDENTIFIER, Pair.Value.x.ToString());
                            Writer.WriteAttributeString(Y_IDENTIFIER, Pair.Value.y.ToString());
                            Writer.WriteAttributeString(Z_IDENTIFIER, ZERO);
                            Writer.WriteAttributeString(W_IDENTIFIER, ZERO);
                        }
                        Writer.WriteEndElement();
                        Writer.WriteStartElement(INTEGER_IDENTIFIER);
                        {
                            Writer.WriteAttributeString(NAME_IDENTIFIER, WIDTH_IDENTIFIER);
                            Writer.WriteAttributeString(VALUE_IDENTIFIER, Pair.Value.w.ToString());
                        }
                        Writer.WriteEndElement();
                        Writer.WriteStartElement(INTEGER_IDENTIFIER);
                        {
                            Writer.WriteAttributeString(NAME_IDENTIFIER, HEIGHT_IDENTIFIER);
                            Writer.WriteAttributeString(VALUE_IDENTIFIER, Pair.Value.h.ToString());
                        }
                        Writer.WriteEndElement();
                    }
                    Writer.WriteEndElement();
                }
            }
            Writer.WriteEndElement();
        }

        public void Convert(string SourceDirectory, string DestinationFileName)
        {
            List<string> Files = new List<string>(Directory.GetFiles(SourceDirectory, SOURCE_EXT_FILTER));

            string DefinitionsFile = Path.Combine(SourceDirectory, DEFINITIONS_FILE);
            if (!Files.Contains(DefinitionsFile))
            {
                throw new System.ApplicationException(ERROR_DEFINITIONS_NOT_FOUND);
            }

            Files.Remove(DefinitionsFile);

            if (Files.Count > 0)
            {
                XmlWriterSettings Settings = new XmlWriterSettings();
                Settings.Indent = true;
                Directory.CreateDirectory(Path.GetDirectoryName(DestinationFileName));
                XmlWriter Writer = XmlWriter.Create(DestinationFileName, Settings);
                Writer.WriteStartDocument();
                {
                    Writer.WriteStartElement(WORLD_IDENTIFIER);
                    {
                        Writer.WriteAttributeString(NAME_IDENTIFIER, BATTLE_CITY);
                        WriteSpriteData(DefinitionsFile, Writer);

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

            Reader.Close();

            if (!(MappedData.ContainsKey(IN_TILES_X_IDENTIFIER)     && MappedData[IN_TILES_X_IDENTIFIER]    != null
                && MappedData.ContainsKey(IN_TILES_Y_IDENTIFIER)    && MappedData[IN_TILES_Y_IDENTIFIER]    != null
                && MappedData.ContainsKey(TILE_WIDTH_IDENTIFIER)    && MappedData[TILE_WIDTH_IDENTIFIER]    != null
                && MappedData.ContainsKey(TILE_HEIGHT_IDENTIFIER)   && MappedData[TILE_HEIGHT_IDENTIFIER]   != null
                && MappedData.ContainsKey(DATA_IDENTIFIER)          && MappedData[DATA_IDENTIFIER]          != null
                ))
            {
                throw new System.ApplicationException(ERROR_MALFORMED_XML);
            }
            
            string[] Entities = MappedData[DATA_IDENTIFIER].Replace(NEWLINE, EMPTY_STR).Split(COMMA_SEPARATOR);
            int CurrentPosition = 0;

            Writer.WriteStartElement(SECTOR_IDENTIFIER);
            {
                Writer.WriteAttributeString (NAME_IDENTIFIER, Path.GetFileNameWithoutExtension(SourceFile));
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
                for (int i = 0; i < Int32.Parse(MappedData[IN_TILES_X_IDENTIFIER]); ++i)
                {
                    for (int j = 0; j < Int32.Parse(MappedData[IN_TILES_Y_IDENTIFIER]); ++j)
                    {
                        Writer.WriteStartElement(ENTITY_IDENTIFIER);
                        {
                            // Check which Object this tile "collides" with.
                            foreach (var Pair in SpriteMappedData)
                            {
                                float y = (int.Parse(Entities[CurrentPosition]) / int.Parse(MappedData[IN_TILES_X_IDENTIFIER])) * float.Parse(MappedData[TILE_HEIGHT_IDENTIFIER]);
                                float x = (int.Parse(Entities[CurrentPosition]) % int.Parse(MappedData[IN_TILES_X_IDENTIFIER])) * float.Parse(MappedData[TILE_WIDTH_IDENTIFIER]);

                                // Slightly reducing the bounding box, otherwise unwanted collisions occur
                                if (Pair.Value.Intersects(
                                    x + BOUNDING_BOX_TOLERANCE,
                                    y + BOUNDING_BOX_TOLERANCE,
                                    int.Parse(MappedData[TILE_WIDTH_IDENTIFIER]) - BOUNDING_BOX_TOLERANCE,
                                    int.Parse(MappedData[TILE_HEIGHT_IDENTIFIER]) - BOUNDING_BOX_TOLERANCE
                                    ))
                                {
                                    if (Pair.Value.classname != null && Pair.Value.classname != "")
                                    {
                                        Writer.WriteAttributeString(CLASS_IDENTIFIER, Pair.Value.classname);
                                    }

                                    break;
                                }
                            }
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
    }
}
