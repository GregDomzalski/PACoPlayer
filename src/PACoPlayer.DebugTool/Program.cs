using System.Text.Json;
using BinForge;
using PACoPlayer.Decoder;
using PACoPlayer.Decoder.Records;

namespace PACoPlayer.DebugTool;

public static class Program
{
    public static void Main(string[] args)
    {
        if (args.Length != 1)
        {
            Console.Error.WriteLine("Expected usage: PACoPlayer.DebugTool.exe <path>");

            return;
        }

        byte[] pacoFile = File.ReadAllBytes(args[0]);
        SpanReader reader = new(pacoFile);

        FileHeader fileHeader = FileDecoder.DecodeHeader(ref reader);
        ChunkHeader[] chunkHeaders = FileDecoder.DecodeChunkHeaders(ref reader, fileHeader.ChunkCount);

        JsonSerializerOptions serializerOptions = new() { WriteIndented = true };
        Console.WriteLine(JsonSerializer.Serialize(fileHeader, serializerOptions));
        Console.WriteLine(JsonSerializer.Serialize(chunkHeaders, serializerOptions));
    }
}
