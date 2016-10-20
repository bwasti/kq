class Screen {
  /* private */
  resize() {
    this.canvas.width = document.body.clientWidth;
    this.canvas.height = document.body.clientHeight;
    let keep_width = this.canvas.width/this.canvas.height < 16.0/9;
    if (keep_width) {
      let height = this.canvas.width * 9 / 16.0;
      this.y_offset = (this.canvas.height - height)/2;
      this.x_offset = 0;
      this.scale = height / this.pixels;
      console.log(this);
    } else {
      let width = this.canvas.height * 16 / 9.0;
      this.x_offset = (this.canvas.width - width)/2;
      this.y_offset = 0;
      this.scale = this.canvas.height / this.pixels;
      console.log(this);
    }

    let i = 0;
    for (let i_ = 0; i_ < this.screen.length; i_ += this.pixels * 16 / 9) {
      for (let j = 0; j < this.pixels * 16 / 9; j++) {
        this.drawPixel(j, i, this.screen[i_ + j]);
      }
      i++;
    }
  }

  drawPixel(x, y, c) {
    this.context.fillStyle = c;
    this.context.fillRect(this.x_offset + this.scale * x,
                          this.y_offset + this.scale * y,
                          this.scale * 0.9, this.scale * 0.9);
  }

  /* public */
  constructor(canvas, resolution = 360) {
    this.canvas = canvas;
    this.context = this.canvas.getContext('2d');
    this.pixels = resolution;
    this.screen = new Array(this.pixels * this.pixels * 16 / 9);
    this.resize();
    window.addEventListener('resize', this.resize.bind(this), false);
  }

  draw(x, y, c) {
    this.drawPixel(x, y, c);
    this.screen[x + y * this.pixels * 16 / 9] = c;
  }

  get(x, y) {
    return this.screen[x + y * this.pixels * 16 / 9]
  }
}

class Asset {
  /* frames : action -> bitmap */
  constructor(frames, screen) {
    this.frames = frames;
    this.screen = screen;
    // TODO: this.width, this.height
  }

  draw(x, y, action) {
    this.bitmap = this.frames[action];
    this.drawAsset(x, y);
  }

  drawAsset(x, y) {
    for (let i = 0; i < this.height; i++) {
      for (let j = 0; j < this.width; j++) {
        this.screen.draw(x + i, y + j, this.old_state[i][j]);
      }
    }
    for (let i = 0; i < this.height; i++) {
      for (let j = 0; j < this.width; j++) {
        this.old_state[i][j] = this.screen.get(x + i, y + j);
        this.screen.draw(x + i, y + j, this.bitmap[i][j]);
      }
    }
  }
}

class Game {
}

