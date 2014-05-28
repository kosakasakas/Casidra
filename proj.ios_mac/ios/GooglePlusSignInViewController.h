//
//  GooglePlusSignInViewController.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/05/26.
//
//

#import <UIKit/UIKit.h>
#import "GPPSignIn.h"

@class GPPSignInButton;

@interface GooglePlusSignInViewController : UIViewController <GPPSignInDelegate>
@property (retain, nonatomic) IBOutlet GPPSignInButton *signInButton;

@end
