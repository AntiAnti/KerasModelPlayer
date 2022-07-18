# Keras Model Player
UE5 plugin to play lightweight neural models.

This is UE5 wrapper for [keras2cpp](https://github.com/gosha20777/keras2cpp) library by [gosha20777](https://github.com/gosha20777). The library uses native C++ code only, and it can be compiled for many platforms. This is a huge advantage, because lightweight neural network trained with Keras can be executed on platforms which doesn't supported, for example, by PyTorch. The plugin was packaged for Windows, Linux, Android and Holographic Windows 10 (HoloLens 2).

*Please read about limitations of this library by the link above.* In brief, it doesn't support Conv3D and GRU/CNN layers.

## Save neural network model

1. Download [keras2cpp](https://github.com/gosha20777/keras2cpp) sources and connect to your Python project:
```
import sys
sys.path.insert(0, '../keras2cpp')
```
2. Train your model at Python with Keras.
3. Save it to file:
```
from keras2cpp import export_model
export_model(MyTrainedModel, 'example.k2c')
```

For more detailed info, read keras2cpp documentation.

## Load model in UE5

The plugin exposes to blueprints only basic functional, so I strongly recommend to use C++.

```
(MyActor.h)
UKerasModel* MyModel;
(MyActor.cpp)
FString FileName = FPaths::ProjectDir() / TEXT("example.k2c");
UKerasFunctionLibrary::CreateKerasModelFromFile(this, FileName, MyModel);
```

## Create and use tensor

```
FKerasTensor InputData;
// Set tensor dimenstions
InputData.Resize({ 4 });
// Fill tensor data
InputData.FromArray({ 1.f, 0.f, 4.f, 2.f});
// How to read value
UE_LOG(LogTemp, Log, TEXT("Input data at position index 2 (%f) is equal to 4"), InputData.GetValueByAddress({ 2 }));
// Convert to one-dim array
TArray<float> TensorData;
InputData.GetAsFlatArray(TensorData);
```

## Evaluate

```
FKerasTensor InputData, OutputData;
InputData.Resize({ 4 });
InputData.FromArray({ 1.f, 0.f, 4.f, 2.f});

if (MyModel->IsLoaded())
{
  MyModel->Evaluate(InputData, OutputData);

  // get dimensions of the output tensor
  TArray<int32> OutDataDims;
  OutputData.GetSize(OutDataDims);
}
```

## Blueprints

For blueprints usage, see demo project.
