//
//  ViewController.m
//  testScreenRotate
//
//  Created by liangkun on 2017/11/6.
//  Copyright © 2017年 liangkun. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) UIButton *landScapeButton;

@property (nonatomic, strong) UIButton *potraitButton;


@end

@implementation ViewController

- (void)viewDidLoad {
    
    
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(orientationDidChange:) name:UIDeviceOrientationDidChangeNotification object:nil];
    
    //横屏的按钮
    _landScapeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    _landScapeButton.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:_landScapeButton];
    
    [_landScapeButton setTitle:@"横屏" forState:UIControlStateNormal];
    
    _landScapeButton.frame = CGRectMake(10, 10, 50, 50);
   
    [_landScapeButton addTarget:self action:@selector(goLandScape) forControlEvents:UIControlEventTouchUpInside];
    
    
    
    //竖屏的按钮
    _potraitButton =  [UIButton buttonWithType:UIButtonTypeCustom];
    _potraitButton.backgroundColor = [UIColor lightGrayColor];
    
    [self.view addSubview:_potraitButton];
    
    [_potraitButton setTitle:@"竖屏" forState:UIControlStateNormal];
    
    _potraitButton.frame = CGRectMake(100, 100, 50, 50);
    
    [_potraitButton addTarget:self action:@selector(goPotrait) forControlEvents:UIControlEventTouchUpInside];
    
}


//转屏结束以后调用的方法
- (void)orientationDidChange:(NSNotification *)noti
{
    
}
- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    
    
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    
    return UIInterfaceOrientationMaskAll;
    
}


- (void)viewWillLayoutSubviews
{
    
    
}
- (void)goLandScape
{
    
    if ([[UIDevice currentDevice]respondsToSelector:@selector(setOrientation:)])
    {
        NSNumber *num = [[NSNumber alloc]initWithInt:(UIInterfaceOrientationLandscapeRight)];
        
    [[UIDevice currentDevice]performSelector:@selector(setOrientation:)withObject:(id)num];
        
        [UIViewController attemptRotationToDeviceOrientation];//这行代码是关键
    }
    
    SEL selector=NSSelectorFromString(@"setOrientation:");
    
    NSInvocation *invocation =[NSInvocation invocationWithMethodSignature:[UIDevice instanceMethodSignatureForSelector:selector]];
    
    [invocation setSelector:selector];
    
    [invocation setTarget:[UIDevice currentDevice]];
    
    int val = UIInterfaceOrientationLandscapeRight;
    
    [invocation setArgument:&val atIndex:2];
    
    [invocation invoke];
    
}

- (void)goPotrait
{
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
