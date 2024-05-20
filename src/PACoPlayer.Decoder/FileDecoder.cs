// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using BinForge;
using PACoPlayer.Decoder.DataTypes;
using PACoPlayer.Decoder.Records;

namespace PACoPlayer.Decoder;

public static class FileDecoder
{
    public static FileHeader DecodeHeader(ref SpanReader reader) =>
        new()
        {
            Version = new(reader.ReadByte(), reader.ReadByte()),
            HeaderSize = reader.ReadInt16BigEndian(),
            Dimensions = new(reader.ReadInt16BigEndian(), reader.ReadInt16BigEndian()),
            DefaultDelay = Delay.From(reader.ReadInt16BigEndian()),
            Bits1 = reader.ReadUInt16BigEndian(),
            ChunkAllocation = reader.ReadInt32BigEndian(),
            CoalescedChunkAllocation = reader.ReadInt32BigEndian(),
            SoundAllocation = reader.ReadInt32BigEndian(),
            FrameCount = reader.ReadInt16BigEndian(),
            ChunkCount = reader.ReadInt16BigEndian(),
            Bits4 = reader.ReadByte(),
            BitDepth = BitDepth.From(reader.ReadByte()),
            PackerVersion = reader.ReadInt16BigEndian(),
            Bits2 = reader.ReadUInt16BigEndian(),
            Bits3 = reader.ReadUInt16BigEndian(),
            FinishedFrames = reader.ReadInt16BigEndian(),
        };

    public static ChunkHeader[] DecodeChunkHeaders(ref SpanReader reader, int chunkCount)
    {
        ChunkHeader[] headers = new ChunkHeader[chunkCount];

        for (int i = 0; i < chunkCount; i++) { headers[i] = DecodeChunkHeader(ref reader); }

        return headers;
    }

    public static ChunkHeader DecodeChunkHeader(ref SpanReader reader) =>
        new(reader.ReadUInt32BigEndian());

    public static ReadOnlySpan<byte> ReadNextChunk(ref SpanReader reader, int chunkLength) =>
        reader.ReadBytes(chunkLength);
}
