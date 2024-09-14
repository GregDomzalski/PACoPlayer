// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace PACoPlayer.AvaloniaUI;

public partial class MainWindowViewModel : ObservableObject
{
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
    private string? _selectedOpcode;

    public Func<Task<string?>>? ShowOpenFileDialog { get; set; }

    [RelayCommand]
    private async Task OpenFile()
    {
        string? filePath = await ShowOpenFileDialog!();

        if (filePath != null)
        {
            // Handle file opening logic
        }
    }

    [RelayCommand]
    private static void Exit() =>
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

    partial void OnSelectedOpcodeChanged(string? value)
    {
        if (value != null)
        {
            // Handle opcode selection changed
        }
    }
}
