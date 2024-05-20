using System.Diagnostics.CodeAnalysis;
using BinForge;
using PACoPlayer.Decoder;
using PACoPlayer.Decoder.Records;

namespace PACoPlayer.DebugTool;

public static class Program
{
    public static void Main(string[] args)
    {
        if (args.Length != 2)
        {
            Console.Error.WriteLine("Expected usage: PACoPlayer.DebugTool.exe <palette> <file>");

            return;
        }

        ReadPalette(args[0]);
        ReadVideoFile(args[1]);
    }

    private static void ReadPalette(string filePath)
    {
        byte[] paletteFile = File.ReadAllBytes(filePath);
        SpanReader paletteReader = new(paletteFile);
        Palette palette = PaletteDecoder.DecodePalette(ref paletteReader, 256);
        Console.WriteLine(palette.ToString());
    }

    [SuppressMessage("Globalization", "CA1303:Do not pass literals as localized parameters")]
    private static void ReadVideoFile(string filePath)
    {
        byte[] pacoFile = File.ReadAllBytes(filePath);
        SpanReader reader = new(pacoFile);

        FileHeader fileHeader = FileDecoder.DecodeHeader(ref reader);
        ChunkHeader[] chunkHeaders = FileDecoder.DecodeChunkHeaders(ref reader, fileHeader.ChunkCount);

        Console.WriteLine(fileHeader);

        int i = 0;
        foreach (ChunkHeader c in chunkHeaders)
        {
            Console.WriteLine($"{i++:D4}: [{c}]");
        }

        i = 0;
        foreach (ChunkHeader header in chunkHeaders)
        {
            Console.WriteLine($"=== Chunk {i++:D3}: ===");
            ReadOnlySpan<byte> chunk = reader.ReadBytes(header.Length);

            OpHeader[] opCodes = ChunkDecoder.DecodeOpcodes(chunk);

            foreach (OpHeader o in opCodes)
            {
                Console.WriteLine(o);
            }

            Console.WriteLine("==================");
            Console.WriteLine();
        }
    }
}
