// void draw_line(t_data *data, int x, int y, int x1, int y1)
// {
//     int dx, dy, err, sx,sy,e2;

//     dx = abs(x1 - x);
//     dy = -abs(y1 - y);
//     sx = x < x1 ? 1 : -1;
//     sy = y < y1 ? 1 : -1;
//     err = dx + dy;
//     while (1)
//     {
//         my_mlx_pixel_put(x, y, data, data->player->color);
//         e2 = 2 * err;
//         if (e2 >= dy) 
//         { 
//             if (x == x1)
//                 break;
//             err += dy;
//             x += sx;
//          }
//          if (e2 <= dx) 
//         {
//             if (y == y1) 
//                  break;
//             err += dx;
//             y += sy;
//          }
//     }
// }
