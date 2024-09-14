// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using BinForge;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PACoPlayer.Decoder;
using PACoPlayer.Decoder.Records;

namespace PACoPlayer.AvaloniaUI;

public class PacoFile
{
    private int _currentChunkIndex;

    public required FileHeader FileHeader { get; init; }
    public required IList<ChunkHeader> ChunkHeaders { get; init; }
    public required IList<Chunk> ChunkData { get; init; }

    public int CurrentChunkIndex
    {
        get => _currentChunkIndex;
        set
        {
            if (value < 0 || value >= ChunkHeaders.Count)
            {
                throw new ArgumentOutOfRangeException(nameof(value), "Chunk index is out of range.");
            }
            _currentChunkIndex = value;
        }
    }

    public ChunkHeader CurrentChunkHeader => ChunkHeaders[CurrentChunkIndex];

    public Chunk CurrentChunk => ChunkData[CurrentChunkIndex];

    public void NextChunk()
    {
        if (CurrentChunkIndex < ChunkHeaders.Count - 1)
        {
            CurrentChunkIndex++;
        }
    }

    public void PreviousChunk()
    {
        if (CurrentChunkIndex > 0)
        {
            CurrentChunkIndex--;
        }
    }
}

public class Chunk
{
    private int _currentOpcodeIndex;

    public required IList<OpHeader> OpCodes { get; init; }

    public int CurrentOpcodeIndex
    {
        get => _currentOpcodeIndex;
        set
        {
            if (value < 0 || value >= OpCodes.Count)
            {
                throw new ArgumentOutOfRangeException(nameof(value), "Opcode index is out of range.");
            }
            _currentOpcodeIndex = value;
        }
    }

    public OpHeader CurrentOpcode => OpCodes[CurrentOpcodeIndex];

    public void NextOpcode()
    {
        if (CurrentOpcodeIndex < OpCodes.Count - 1)
        {
            CurrentOpcodeIndex++;
        }
    }

    public void PreviousOpcode()
    {
        if (CurrentOpcodeIndex > 0)
        {
            CurrentOpcodeIndex--;
        }
    }
}

[SuppressMessage("Performance", "CA1822:Mark members as static")]
public partial class MainWindowViewModel : ObservableObject
{
    private PacoFile? _openedFile;

    [ObservableProperty]
    private string _currentFrame = "001 of 234";

    [ObservableProperty]
    private string _videoDimensions = "1920x1080";

    [ObservableProperty]
    private string _fps = "30";

    [ObservableProperty]
    private string _debugOutput = "0x00 0x01 0x02 0x03\n0x04 0x05 0x06 0x07\n0x08 0x09 0x0A 0x0B";

    [ObservableProperty]
    private ObservableCollection<string> _opcodes =
    [
        "Opcode 1",
        "Opcode 2",
        "Opcode 3",
    ];

    [ObservableProperty]
    private int _selectedOpcodeIndex;

    public Func<Task<string?>>? ShowOpenFileDialog { get; set; }

    [RelayCommand]
    private async Task OpenFile()
    {
        string? filePath = await ShowOpenFileDialog!();

        if (filePath != null)
        {
            _openedFile = ParseFile(filePath);
            VideoDimensions = _openedFile.FileHeader.Dimensions.ToString();
            CurrentFrame = $"001 of {_openedFile.FileHeader.FrameCount:D3}";
            Fps = _openedFile.FileHeader.DefaultDelay.ToString();
            Opcodes.Clear();
            _openedFile.CurrentChunk.OpCodes.Select(o => o.Kind).ToList().ForEach(o => Opcodes.Add(o.ToString()));
            DebugOutput = _openedFile.CurrentChunk.CurrentOpcode.ToString();
        }
    }

    private static PacoFile ParseFile(string path)
    {
        byte[] data = File.ReadAllBytes(path);

        SpanReader reader = new(data);
        FileHeader fileHeader = FileDecoder.DecodeHeader(ref reader);
        ChunkHeader[] chunkHeaders = FileDecoder.DecodeChunkHeaders(ref reader, fileHeader.ChunkCount);

        PacoFile pacoFile = new()
        {
            FileHeader = fileHeader,
            ChunkHeaders = chunkHeaders,
            ChunkData = new Chunk[chunkHeaders.Length],
        };

        for (int i = 0; i < chunkHeaders.Length; i++)
        {
            ReadOnlySpan<byte> chunk = reader.ReadBytes(chunkHeaders[i].Length);
            OpHeader[] opCodes = ChunkDecoder.DecodeOpcodes(chunk);
            pacoFile.ChunkData[i] = new() { OpCodes = opCodes };
        }

        return pacoFile;
    }

    [RelayCommand]
    private void Exit() =>
        Environment.Exit(0);

    [RelayCommand]
    private static void Restart()
    {
        // Implement restart logic
    }

    [RelayCommand]
    private static void StepBackward()
    {
        // Implement step backward logic
    }

    [RelayCommand]
    private static void Play()
    {
        // Implement play logic
    }

    [RelayCommand]
    private static void StepForward()
    {
        // Implement step forward logic
    }

    [RelayCommand]
    private static void FastForward()
    {
        // Implement fast-forward logic
    }

    partial void OnSelectedOpcodeIndexChanged(int value)
    {
        if (value < 0 || value >= Opcodes.Count) { return; }

        if (_openedFile == null) { return; }

        _openedFile.CurrentChunk.CurrentOpcodeIndex = value;
        DebugOutput = _openedFile.CurrentChunk.CurrentOpcode.ToString();

        //DebugOutput = BitConverter.ToString(_openedFile.CurrentChunk.CurrentOpcode).Replace("-", " ");
    }

}
