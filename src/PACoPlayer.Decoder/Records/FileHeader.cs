// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text.Json.Serialization;
using PACoPlayer.Decoder.DataTypes;
using Version = PACoPlayer.Decoder.DataTypes.Version;

namespace PACoPlayer.Decoder.Records;

public record FileHeader
{
    public Version Version { get; init; }
    public int HeaderSize { get; init; }
    public Rectangle Dimensions { get; init; }
    public Delay DefaultDelay { get; init; } = Delay.From(0);

    [JsonIgnore]
    public ushort Bits1 { get; init; }

    public bool UserInterrupt => BitMask.Get(Bits1, 15, 1) == 1;
    public bool ChangeBitDepth => BitMask.Get(Bits1, 14, 1) == 1;
    public bool BlankFullScreen => BitMask.Get(Bits1, 13, 1) == 1;
    public bool FileLoading => BitMask.Get(Bits1, 12, 1) == 1;
    public bool ChunkCoalescing => BitMask.Get(Bits1, 11, 1) == 1;
    public bool Loop => BitMask.Get(Bits1, 10, 1) == 1;
    public bool NoTransitionOps => BitMask.Get(Bits1, 9, 1) == 1;
    public bool MaintainFramerate => BitMask.Get(Bits1, 8, 1) == 1;
    public int RepeatXPixels => (int)BitMask.Get(Bits1, 6, 3);
    public bool HighLevelBlit => BitMask.Get(Bits1, 5, 1) == 1;
    public bool ExactBitdepthOnly => BitMask.Get(Bits1, 4, 1) == 1;
    public bool EatStoppingEvent => BitMask.Get(Bits1, 3, 1) == 1;
    public int RepeatYPixels => (int)BitMask.Get(Bits1, 0, 7);

    public int ChunkAllocation { get; init; }
    public int CoalescedChunkAllocation { get; init; }
    public int SoundAllocation { get; init; }

    public int FrameCount { get; init; }
    public int ChunkCount { get; init; }

    [JsonIgnore]
    public byte Bits4 { get; init; }

    public bool DebugVersion => BitMask.Get(Bits4, 2, 1) == 1;
    public bool VerticalBlankSync => BitMask.Get(Bits4, 1, 1) == 1;
    public bool BackgroundColor => BitMask.Get(Bits4, 0, 1) == 1;

    public BitDepth BitDepth { get; init; } = BitDepth.From(0);

    public int PackerVersion { get; init; }

    [JsonIgnore]
    public ushort Bits2 { get; init; }

    public bool Interlaced => BitMask.Get(Bits2, 15, 1) == 1;
    public bool Indirect => BitMask.Get(Bits2, 14, 1) == 1;
    public bool SmallerPacking => BitMask.Get(Bits2, 13, 1) == 1;
    public int SoundSampleRate => (int)BitMask.Get(Bits2, 11, 3); // TODO: Probably an enum?
    public int SoundMinutes => (int)BitMask.Get(Bits2, 6, 0x1F);
    public int SoundSeconds => (int)BitMask.Get(Bits2, 0, 0x3F);

    [JsonIgnore]
    public ushort Bits3 { get; init; }

    public bool SoundFramerate => BitMask.Get(Bits3, 15, 1) == 1;
    public bool WaitAtEnd => BitMask.Get(Bits3, 14, 1) == 1;
    public int PackerVersionHigh => (int)BitMask.Get(Bits3, 0, 0x3FFF);

    public int FinishedFrames { get; init; }
}
